#include "Manager/FireWireManager.hpp"

namespace stereo {

FireWireManager::FireWireManager(std::string configDir, std::string logDir,std::string rootLeft,std::string rootRight)
{
	//sets all the thread running flags to false
	dc1394Running_=false;
	debayerRunning_=false;
	
	leftDir_=rootLeft;
	rightDir_=rootRight;
	
	currentState_=Initializing;
	oLog=spdlog::basic_logger_mt("FireWireManager", logDir); //create a logger
	oLog->set_pattern("[%H:%M:%S:%e] [thread %t] %v ");//set the log format to time, thread number
	
	
	//Load the internal camera settings such as brightness etc from configDir
	cv::FileStorage inFile(configDir,cv::FileStorage::READ); //open xml file
	oLog->info("Loaded BumbleBee Settings from " + configDir);
	
	//always assumes the tag name given was RecordingSettings 
	inFile["RecordingSettings"]>>cameraConfig_;
	inFile.release();//close file
	
	
	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
}


FireWireManager::FireWireManager(std::string logDir,std::string rootLeft,std::string rootRight)
{
		//sets all the thread running flags to false
	dc1394Running_=false;
	debayerRunning_=false;
	
	currentState_=Initializing;
	
	leftDir_=rootLeft;
	rightDir_=rootRight;
	oLog=spdlog::basic_logger_mt("FireWireManager", logDir);
	oLog->set_pattern("[%H:%M:%S:%e] [thread %t] %v ");
	
	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
}

FireWireManager::~FireWireManager()
{
	oLog->info("FireWireManager destructor called");
}


//////////////////
//private
///////////internal states
void FireWireManager::processCommandQ()
{
	
	ReadLock comRQLock(mutex_commandQ_);//command Read Queue lock
	int commandSize=commandQ_.size();
	comRQLock.unlock();
	std::stringstream msg_;//message buffer
	if(commandQ_.size()>0)
	{
		//attain a writing lock to pop the front of the queue
		WriteLock comWQLock(mutex_commandQ_);
		FireWireCommands toProcess=commandQ_.front(); //Read it
		commandQ_.pop();//delete it from queue
		comWQLock.unlock();//unlock the mutex
		//update the internal State
		switch(toProcess)
		{
			case Stop:
			{
				WriteLock stateWLock(mutexState_);
				switch(currentState_)
				{
					case Closing:
					{
						oLog->critical("FireWireManager already attempting to close");
						break;
					}
					case Recording:
					{
							dc1394_video_set_transmission(camera_,DC1394_OFF);
							currentState_=Closing;
							oLog->info("Set Closing State");
							break;
					}
					
				}
				stateWLock.unlock();
				break;
			}
			default:
			{
				oLog->critical("Invalid Command recieved from VideoManager");
				break;
			}
			
		}
	}
}




//external interfaces
///////////////////

void FireWireManager::SendCommand(FireWireManager::FireWireCommands command)
{
	//add a command to the queue for processing in the mainThread
	WriteLock commandLock(mutex_commandQ_);
	commandQ_.push(command);
	commandLock.unlock();

}

FireWireManager::FireWireState FireWireManager::getCurrentState()
{
	ReadLock stateRLock(mutexState_);
	return currentState_;
}

std::string FireWireManager::StateToString(FireWireManager::FireWireState inState)
{
	switch(inState)
	{
		case Initializing:
		{
			return "Initializing";
			break;
		}
		case Recording:
		{
			return "Recording";
			break;
		}
		case Closing:
		{
			return "Closing";
			break;
		}
		case FAILED:
		{
			return "Failed";
			break;
		}
		case ShutDown:
		{
			return "Shutdown";
			break;
		}
	}
}




///////////////////
//Thread functions
//////////////////


void FireWireManager::mainLoop()
{
	
	boost::thread *dc1394Thread_;		//copies from DMA ring buffer 
	boost::thread *debayerThread_; //debayers and sets image Region of interests

	
	oLog->info("entered Main Loop");
	bool killLoop=false;
	/////////////////////////
	///Initialize the Camera
	///////////////////////
	if(!InitializeDC1394())//if libdc1394 failed to contact the camera
	{

		killLoop=true;
		
		WriteLock stateLock(mutexState_);
		currentState_=FAILED;
		stateLock.unlock();
	}
	else
	{
		//check the settings are correct
		if(UpdateSettings())
		{//if they are valid and were set, then enter the waiting state			
			oLog->info("FireWireManager initialized, entering Wait State");
			WriteLock stateLock(mutexState_);
			currentState_=Recording;
			stateLock.unlock();
			//instantiate the Threads
			dc1394Thread_= new boost::thread(&FireWireManager::getDC1394Frame,this);
			debayerThread_= new boost::thread(&FireWireManager::debayerFrame,this);

			//Record command Received
			WriteLock stateWLock(mutexState_);
			currentState_=Recording;
			oLog->info("Recording State Set");	
			dc1394_video_set_transmission(camera_,DC1394_ON);
			stateWLock.unlock();
			killLoop=false;
		}
		else
		{
			//if settings were wrong, killLoop
			killLoop=true;
			WriteLock stateLock(mutexState_);
			currentState_=FAILED;
			stateLock.unlock();
		}
	}
	
	
	
	
	while(!killLoop)
	{
		processCommandQ();
		FireWireState readState=getCurrentState();
		
		switch(readState)
		{
			case Closing:
			{
				oLog->info("FireWire Terminate acknowledged by main loop");
				killLoop=true;
				break;
			}
			case FAILED:
			{
				oLog->info("ERROR, status set to failed, terminating");
				killLoop=true;
				break;
			}
			usleep(1000);
			
		}

	}
	
	waitThreads();
	if(init_1394_)
	{
		oLog->info("Free libdc1394");
		closeCamera();
	}

	oLog->info("main loop killed, FireWire Terminating");
	
	
	//Maybe join threads here if they were created ? 
	//stopping it from dying without killing the spawned threads
	
}


void FireWireManager::getDC1394Frame()
{
	WriteLock RunningLock(mutex_runningDC1394_);
	dc1394Running_=true;	
	RunningLock.unlock();
	oLog->info("DC1394 Thread Activated");
	
	cv::Mat bayerImage=cv::Mat(1536,1024,CV_8UC1);
	
	bool killLoop=false;
	while(!killLoop)
	{
		FireWireState polledState=getCurrentState();
		switch(polledState)
		{
			case Recording:
			{
				std::stringstream feedbackMsg_;
				//copy from DMA ring buffer to dcQ_ 
				dc1394video_frame_t * latestFrame;
				dc1394video_frame_t BufferFrame;
				dc1394error_t deque,enque;
				
				deque=dc1394_capture_dequeue(camera_,DC1394_CAPTURE_POLICY_WAIT,&latestFrame);
				
				if(deque==DC1394_SUCCESS)
				{
					Frame outframe_;
					//copyMetaData
					memcpy(&BufferFrame,latestFrame,sizeof(dc1394video_frame_t)); //copy MetaData
					BufferFrame.allocated_image_bytes=0;
					BufferFrame.image=NULL;
					
					dc1394_deinterlace_stereo_frames(latestFrame,&BufferFrame,DC1394_STEREO_METHOD_INTERLACED);
					//decode the video message into seperate left and right images (as opposed to mixed)
					
					short int * d_pt=(short int*)&bayerImage.data[0];
					short int * s_pt=(short int*)&BufferFrame.image[0];		
					memcpy(d_pt,s_pt,1536*1024);//copy dc1394 image data into mat structure
					cv::cvtColor(bayerImage,outframe_.outputImage,CV_BayerBG2GRAY);//debayer into gray colour
					outframe_.tstamp_=latestFrame->timestamp;
					
					WriteLock dcQLock(mutex_dcQ_);
					dcQ_.push(outframe_);
					dcQLock.unlock();
					free(s_pt);
				}
				else
				{
					oLog->warn("Deque failed");
				}
				
				enque=dc1394_capture_enqueue(camera_,latestFrame);
				break;
			}
			case Closing:
			{
				oLog->info("Dc1394 Thread Terminate acknowledged");
				killLoop=true;
				break;
			}
			
		}
		
		usleep(1000);
	}

	WriteLock RunningLockClose(mutex_runningDC1394_);
	dc1394Running_=false;	
	RunningLockClose.unlock();
	
}

void FireWireManager::debayerFrame()
{
	WriteLock RunningLock(mutex_runningDebayer_);
	debayerRunning_=true;	
	RunningLock.unlock();
	oLog->info("Debayer Thread Activated");
	
	
	//cv::Mat left_img=outputImage(cv::Rect(0,768,1024,768));
	//cv::Mat right_img=outputImage(cv::Rect(0,0,1024,768));
	
	bool killLoop=false;
	while(!killLoop)
	{
		FireWireState polledState=getCurrentState();
		switch(polledState)
		{
			case Recording:
			{
				//check the size of the frame buffer
				ReadLock dcQRLock(mutex_dcQ_);
				int totalMessages=dcQ_.size();
				dcQRLock.unlock();
				if(totalMessages>0)
				{
					ReadLock dcQRLock(mutex_dcQ_);
					cv::Mat left_img=dcQ_.front().outputImage(cv::Rect(0,768,1024,768));
					cv::Mat right_img=dcQ_.front().outputImage(cv::Rect(0,0,1024,768));
				
					std::stringstream ldir,rdir;
					ldir<<leftDir_<<"/"<<dcQ_.front().tstamp_<<".bmp";
					rdir<<rightDir_<<"/"<<dcQ_.front().tstamp_<<".bmp";

					cv::imwrite(ldir.str(),left_img);
					cv::imwrite(rdir.str(),right_img);
					
					dcQRLock.unlock();
					
					WriteLock dcQWLock(mutex_dcQ_);
					dcQ_.pop();
					dcQWLock.unlock();
					oLog->info(ldir.str().c_str());
				}
				break;
			}
			case Closing:
			{
				oLog->info("Debayer Thread Terminate acknowledged");
				killLoop=true;
				break;
			}
		}
		usleep(50);
	}
	
	WriteLock RunningLockClose(mutex_runningDebayer_);
	debayerRunning_=true;	
	RunningLockClose.unlock();
}






void FireWireManager::waitThreads()
{
	
	bool ThreadsClosed=false;
	bool localCopyDC1394;
	bool localCopyDebayer;
	while(!ThreadsClosed)
	{
		//lock each state and copy them
		ReadLock dcLock(mutex_runningDC1394_);
		localCopyDC1394=dc1394Running_;
		dcLock.unlock();
		
		ReadLock debLock(mutex_runningDebayer_);
		localCopyDebayer=debayerRunning_;
		debLock.unlock();

		
		//if they are all false, then unpause
		if(!localCopyDC1394&&!localCopyDebayer)
		{
			ThreadsClosed=true;
		}
		usleep(2000);
	}
	oLog->info("Thread status -- All closed successfully");	
	WriteLock status(mutexState_);
	currentState_=ShutDown;
	status.unlock();
}








////////////////////
////BumbleBee Related Functions
/////////////////


bool FireWireManager::InitializeDC1394()
{
	//connect to the Camera using libDC1394
	bool Success_=false;
	dc1394error_t err;//error definitions defined by libdc1394
	init_1394_ = dc1394_new (); 
	
	
	if(init_1394_)//if initialized
	{	
		dc1394camera_list_t * list;//get a list of available firewire Cameras
		oLog->info("libdc1394 was found and initialized successfully");
		oLog->info("Connecting to first FireWire Camera in the list");
		err=dc1394_camera_enumerate(init_1394_, &list);//enumerate through the list of cameras
		if(err==DC1394_SUCCESS)
		{
			//std::cout<<"Cameras Detected --  "<<list->num<<std::endl; //keeping for reference purposes
			if(list->num!=0)
			{
				camera_ = dc1394_camera_new(init_1394_, list->ids[0].guid);
				std::stringstream msg_;
				msg_<<"FireWire Camera detected with ID : "<<list->ids[0].guid;
				oLog->info(msg_.str().c_str());
				if(camera_)
				{
					Success_=true;		
				}
			}
			dc1394_camera_free_list (list);
		}
	}
	else
	{
		oLog->error("LIBDC1394 failed to Initialized");
		Success_=false;
	}	
	return Success_;
}

void FireWireManager::closeCamera()
{
	dc1394_camera_free(camera_);
	dc1394_free(init_1394_);
}


bool FireWireManager::UpdateSettings()
{
	if(!init_1394_)
	{
		oLog->critical("Update Settings Failed to take hold as DC1394 has not been initiated");
		return false;
	}
	//attempt to change all the settings at once with new values
	std::vector<dc1394error_t> basic_e,expose_e,balance_e,shutter_e,gain_e,bright_e;
	//holds results of each error code, if any of the vectors are a failure, immediate exit and return false
	cameraConfig_.setBasicSettings(basic_e,camera_);
	if(cameraConfig_.checkUpdated(basic_e))
	{
		cameraConfig_.setBright(bright_e,camera_);
		if(cameraConfig_.checkUpdated(bright_e))
		{
			cameraConfig_.setExposure(expose_e,camera_);
			if(cameraConfig_.checkUpdated(expose_e))
			{
				cameraConfig_.setGain(gain_e,camera_);
				if(cameraConfig_.checkUpdated(gain_e))
				{
					cameraConfig_.setShutter(shutter_e,camera_);
					if(cameraConfig_.checkUpdated(shutter_e))
					{
						cameraConfig_.setWBalance(balance_e,camera_);
						if(cameraConfig_.checkUpdated(balance_e))
						{
							return true;
						}
						else
						{
							oLog->error("Shutter Speed Settings failed to configure");
							return false;
						}
					}
					else
					{
						oLog->error("Shutter Speed Settings failed to configure");
						return false;
					}
				}
				else
				{
					oLog->error("Gain Settings failed to configure");
					return false;
				}
			}
			else
			{
				oLog->error("Exposure Settings failed to configure");
				return false;
			}
			
		}
		else
		{
			oLog->error("Brightness Settings failed to configure");
			return false;
		}
		
		
	}
	else
	{
		oLog->error("Basic Settings failed to configure");
		return false;
	}


	
	
}




}