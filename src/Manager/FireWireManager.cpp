#include "Manager/FireWireManager.hpp"

namespace stereo {

FireWireManager::FireWireManager(std::string configDir, std::string logDir)
{
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


FireWireManager::FireWireManager(std::string logDir)
{
	currentState_=Initializing;
	oLog=spdlog::basic_logger_mt("FireWireManager", logDir);
	oLog->set_pattern("[%H:%M:%S:%e] [thread %t] %v ");
	
	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
	
}

FireWireManager::~FireWireManager()
{
	oLog->info("FireWireManager destructor called");
	if(init_1394_)
	{
		oLog->info("Free libdc1394");
		closeCamera();
	}
}


//////////////////
//private
///////////internal states
void FireWireManager::processCommandQ()
{
	ReadLock comRQLock(mutex_commandQ_);//command Read Queue lock
	if(commandQ_.size()>0)
	{
		std::stringstream msg_;//message buffer
		msg_<<"command Queue Size : "<<commandQ_.size();
		oLog->info(msg_.str().c_str());
		comRQLock.unlock();
		
		//attain a writing lock to pop the front of the queue
		WriteLock comWQLock(mutex_commandQ_);
		FireWireCommands toProcess=commandQ_.front(); //Read it
		commandQ_.pop();//delete it from queue
		comWQLock.unlock();//unlock the mutex
		//update the internal State
		switch(toProcess)
		{
			case Record:
			{	
				//Record command Received
				WriteLock stateWLock(mutexState_);
				if(currentState_&Waiting)
				{
					currentState_=Recording;
					oLog->info("Recording State Set");	
					dc1394_video_set_transmission(camera_,DC1394_ON);
				}
				else
				{
					oLog->info("Cannot transition to Recording State");
				}
				stateWLock.unlock();
				break;
			}
			case Stop:
			{
				WriteLock stateWLock(mutexState_);
				if(currentState_&Recording) //if state is recording
				{
					currentState_=Closing;
					oLog->info("Set Closing State");
				}
				else
				{
					oLog->info("Invalid State, cannot transition from recording");
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
		case Waiting:
		{
			return "Waiting";
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
	}
}




///////////////////
//Thread functions
//////////////////


void FireWireManager::mainLoop()
{
	
	boost::thread *dc1394Thread_;		//copies from DMA ring buffer 
	boost::thread *debayerThread_; //debayers and sets image Region of interests
	boost::thread *copyLeftThread_;//copies to the hard drive
	boost::thread *copyRightThread_;//copies to the hard drive
	
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
			currentState_=Waiting;
			stateLock.unlock();
			
			//instantiate the Threads
			
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
		usleep(1000);
	}
	oLog->info("main loop killed, FireWire Terminating");
	
	
	//Maybe join threads here if they were created ? 
	//stopping it from dying without killing the spawned threads
	
}


void FireWireManager::getDC1394Frame()
{
	bool killLoop=false;
	while(!killLoop)
	{
		ReadLock stateLock(mutexState_);
		FireWireState polledState=currentState_;
		stateLock.unlock();
		switch(polledState)
		{
			case Recording:
			{
					dc1394video_frame_t * tempFrame;
					dc1394error_t deque,enque;
				
				
				break;
			}
			case Closing:
			{
				//
				break;
			}
			
		}
		
		
		
		usleep(20);
	}
	
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