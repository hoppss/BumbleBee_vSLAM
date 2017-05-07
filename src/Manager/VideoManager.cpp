#include "Manager/VideoManager.hpp"

namespace stereo
{
	
VideoManager::VideoManager()
{
	Initialized_=false;
	Terminate_=false;
	setDefaultOutvar(); //out variables
	
	//if the file structure was created (i.e. true), then begin the logging and ncurses setup
	if(initFiles())
	{
		Initialized_=true;
		oLog=spdlog::basic_logger_mt("system", genfullDir(syslog));
		oLog->set_pattern("[%H:%M:%S:%e] [thread %t] %v ");
		oLog->info("Loaded configuration succesfully, beginning nCurses Window");
		initscr();
		cbreak();
		nodelay(stdscr,TRUE);
		scrollok(stdscr,TRUE);
		noecho();
		keypad(stdscr,TRUE);
	}
	else
	{
		std::cout<<"Failed to create directories, Flag to Terminate"<<std::endl;
	}
}

VideoManager::VideoManager(std::string RecordingSettingsDirectory)
{
	starting_time=std::time(0);
	//Loads with the specified RecordingSettings	
	//recConfig_.readFromFile(RecordingSettingsDirectory);
}


VideoManager::~VideoManager()
{
	oLog->info("Entering VideoManager Destructor");
	//clean up memory
	if(Initialized_)
	{
	addstr("Recording Stopped, push 's' to terminate\n");
	bool loop=true;
	while(loop)
	{
		refresh();
		int pressed_key=getch();
		if(pressed_key=='s')
		{			
				loop=false;
		}
		usleep(100000);
		}
		endwin();
	}
	std::cout<<"VideoManager has been closed";
	
}

void VideoManager::beginRecording()
{
	if(Initialized_)
	{
		oLog->info("Begining Recording Function");
		managerThread_= new boost::thread(&VideoManager::mainManagerThread,this);
		managerThread_->join();
	}
	else
	{
		std::cout<<"Failed initialization, cannot begin recording"<<std::endl;
	}
}

///////////////////////////////////
// INternal utility functions
////////////////////////////////

void VideoManager::setDefaultOutvar()
{
	root_in_dir_=DEFAULT_ROOT_IN_;
	root_out_dir_=DEFAULT_ROOT_OUT_;
	//folder Names
	log_folder_=DEFAULT_LOG_FOLDER_;
	data_folder_=DEFAULT_DATA_FOLDER_;
	l_image_folder_=DEFAULT_LEFTCAMERA_FOLDER_;
	r_image_folder_=DEFAULT_RIGHTCAMERA_FOLDER_;
	//filenames
	syslogName_=DEFAULT_SYSTEM_LOG_NAME_;
	camlogName_=DEFAULT_CAMERA_LOG_NAME_;
	inoutlogName_=DEFAULT_IN_OUT_LOG_NAME_;
	//dynamic variables
	starting_time=std::time(0);
}


//returns a string format from the time_t structure that can be used as a folder name
std::string VideoManager::getStringFormat(time_t inTime)
{
    struct std::tm tstruct;
    char buf[100];
    tstruct = *std::localtime(&inTime);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d__%H-%M-%S", &tstruct);
		std::string outString(buf);
		return outString;
}

//creates the directory structure
bool VideoManager::initFiles()
{
	bool sRoot,sTime,sData,sLog,sLimg,sRimg;//success flag if directory was created
	
	//sRoot=createDir(genfullDir(rootRecordDir));
	//sTime=createDir(genfullDir(rootTimeDir));
	sData=createDir(genfullDir(rootData));
	sLog=createDir(genfullDir(rootLog));
	sLimg=createDir(genfullDir(rootLfolder));
	sRimg=createDir(genfullDir(rootRfolder));
	
	
	if(sData&&sLog&&sLimg&&sRimg)//if all the folders were created return true
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

std::string VideoManager::genfullDir(VideoManager::DIRECTNAME type)
{
	//function that prints out all the possible directory names,
	//DIRECTNAME specifies which folder or log file name you would 
	//like to receive as the output, all relative to the root out directory
		std::string outfile;
		switch(type)
		{
			case rootRecordDir:
			{
				outfile = root_out_dir_;
				break;
			}
			case rootTimeDir:
			{
				outfile=root_out_dir_;
				outfile+="/";
				outfile+=getStringFormat(starting_time);
				break;
			}
			case rootLog:
			{
				outfile=genfullDir(rootTimeDir);
				outfile+="/";
				outfile+=log_folder_;
				break;
			}
			case rootData:
			{
				outfile=genfullDir(rootTimeDir);
				outfile+="/";
				outfile+=data_folder_;
				break;
			}
			case rootLfolder:
			{
				outfile=genfullDir(rootData);
				outfile+="/";
				outfile+=l_image_folder_;
				break;
			}
			case rootRfolder:
			{
				outfile=genfullDir(rootData);
				outfile+="/";
				outfile+=r_image_folder_;
				break;
			}
			case syslog:
			{
				outfile=genfullDir(rootLog);
				outfile+="/";
				outfile+=syslogName_;
				break;
			}
			case camlog:
			{
				outfile=genfullDir(rootLog);
				outfile+="/";
				outfile+=camlogName_;
				break;
			}
			
			default:
			{
				outfile="DIRECTNAME UNKNOWN -- error";
        break;
			}
		}
		return outfile;
}


bool VideoManager::createDir(std::string dir)
{
	//returns true if the directories were succesfully created
	if(!boost::filesystem::exists(dir)) //check if it exists already
	{
		std::string command;
		command="mkdir -p "+dir;
		if(!system(command.c_str())) //if 0, success , else false
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else{
		return true;//directory already exists
	}

}

///////////////////////////////////
/////////Threaded Functions
///////////////////////////////////

void VideoManager::pollThread()
{

	bool killThread=false;
	addstr("Press 's' to stop video recording\n");
	while(!killThread)
	{
		refresh();
		int pressed_key=getch();
		if(pressed_key=='s')
		{			
			killThread=true;
			oLog->info("Terminate acknowledged in PollThread_");
		}
		usleep(10000);
	}	
	WriteLock tLock(mutexTerminate_);
	Terminate_=true;
	tLock.unlock();
	oLog->info("Terminate Status set to True");
}

void VideoManager::mainManagerThread()
{
	////////////
	//handshaking +initialization
	///////////
	

	//Create input output thread
	pollThread_=new boost::thread(&VideoManager::pollThread, this);
	bumbleBee_= new FireWireManager(DEFAULT_FIREWIRESETTINGS_,genfullDir(camlog),genfullDir(rootLfolder),genfullDir(rootRfolder));
	
	bool killLoop=false; //local kill loop entry, this way mutex reading is reduced (i think)

	
	//loop until the FireWiremanager has been configured and has setup libdc1394
	bool configured=false;
	
	while(!configured)
	{
		ReadLock tLock(mutexTerminate_);
		killLoop=Terminate_;
		tLock.unlock();
		if(!killLoop)
		{
			std::stringstream msg_;
			//if no exit command has been sent from the user,check whether FireWireManager is ready
			FireWireManager::FireWireState pollStatus=bumbleBee_->getCurrentState();
			msg_<<"Current FireManager Status received : "<<bumbleBee_->StateToString(pollStatus);
			oLog->info(msg_.str().c_str());
			switch(pollStatus)
			{
				case FireWireManager::Initializing :
				{
					oLog->info("Sending record Still Initializing");
					configured=false;//continue waiting
					killLoop=false;			
					break;
				}
				case FireWireManager::Recording :
				{
					oLog->critical("FireWireManager is running");
					killLoop=false;
					configured=true;
					break;
				}
				case FireWireManager::FAILED :
				{
					oLog->info("FireWiremanager failed to configure correctly, closing");
					killLoop=true;
					configured=true;
					break;
				}
			}
		}
		else
		{
			configured=true;
			killLoop=true;
			oLog->critical("VideoManager terminated before FireWireManager was configured");
		}
		
		usleep(5000);
	}
	

	while(!killLoop)//wait until user has told the program to exit
	{
		ReadLock tLock(mutexTerminate_);
		killLoop=Terminate_;
		tLock.unlock();
		usleep(4000);
	}
	
	oLog->info("Video Manager Terminate command acknowledged, sending Stop command to FireWireManager");
	bumbleBee_->SendCommand(FireWireManager::Stop);
	
	bool wait=true; //true while waiting for FireWireManager to clean up threads and memory
	FireWireManager::FireWireState pollState;//holds the polled firewiremanager internal state
	while(wait)
	{
		pollState=bumbleBee_->getCurrentState();
		if(pollState&FireWireManager::ShutDown)
		{
			wait=false;
			oLog->critical("fireWiremanager has been shutdown");
		}
		usleep(4000);
	}
	
	
	oLog->critical("Kill Main Process signal Acknowledged, mainManagerThread exiting");
}







/*
bool VideoManager::checkForError(std::vector< dc1394error_t >& err)
{
	//cycle through returned error codes, and return false if any are found Unsuccesful
	//failed to set
	bool Error=false;
	for(int index=0;index<err.size();++index)
	{
		if(err.at(index)!=DC1394_SUCCESS)
		{
			Error=true;
		}
	}
	return Error;
}


//////////////////////////


void VideoManager::LatestFrame()
{
	while(recording_)
	{
		
		boost::unique_lock<boost::mutex> lock{mutexLeftQueue_,boost::try_to_lock};
		if(lock.owns_lock())
		{
			my_logger->info("recordThreadLocked");
			leftImgs_.push(2);
			lock.unlock();
		}
		else
		{
			my_logger->info("recordThreadLocked--FAILED");
		}
	}
}

void VideoManager::saveFrame()
{
	while(recording_)
	{
		boost::unique_lock<boost::mutex> lock{mutexLeftQueue_,boost::try_to_lock};
		if(lock.owns_lock())
		{
			my_logger->info("saveThreadLocked");
			leftImgs_.push(10);
			lock.unlock();	
 		}
		else
		{
			my_logger->info("saveThreadLocked--FAILED");
		}
	}
}


///////////////////////////
////PUBLIC FUNCTIONS
////////////////////////


void VideoManager::startRecording()
{
	//begins recording a video sequence
	//spawns two threads
	//thread1-> polling thread for libdc1394,
	//waits until image is available, copies to cv::Mat object if available
	//also monitors the DMA circular buffer and flushes if necessary/WARNS 
	
	//thead2->copies images from a MAT buffer onto the disk
	recording_=true;
	recordThread_=new boost::thread(boost::bind(&VideoManager::LatestFrame,this));
	leftCopyThread_=new boost::thread(boost::bind(&VideoManager::saveFrame,this));
}

void VideoManager::stopRecording()
{
	recording_=false;
}

*/



	
}
