#ifndef FIREWIRE_MANAGER_HEADER_HPP
#define FIREWIRE_MANAGER_HEADER_HPP





/////////////////////
///////Camera related Includes
#include "Manager/FireWireSettings.hpp"
#include "Manager/Frame.hpp"
////////////////////////
////////////////////
#include <iostream>
#include <ctime>
#include <chrono>

#include "spdlog/spdlog.h"

#include <boost/thread.hpp>
#include <queue>

namespace stereo
{
typedef boost::shared_lock<boost::shared_mutex>  ReadLock;
typedef boost::unique_lock<boost::shared_mutex> WriteLock;

class FireWireManager
{	
	public:
		enum FireWireCommands
		{
			Stop=1
		};
		
		//Initializing -> still configuring LIBDC1394 + checking settings
		// when it is completed initializing, it will enter the waiting state, otherwise it will enter
		//the FAILED State
		
		//Waiting -> Manager exists but is currently doing no Work
		//Recording-> All threads running
		
		enum FireWireState
		{
			Initializing=0,
			Recording=2,
			Closing=3,
			FAILED=4,
			ShutDown=5,
		};
		FireWireManager(std::string configDir,std::string logDir,std::string rootLeft,std::string rootRight);//includes XMl firewire settings directory
		FireWireManager(std::string logDir,std::string rootLeft,std::string rootRight);//just the full directory to Log
		~FireWireManager();
		//external interfaces
		void SendCommand(FireWireCommands command);
		FireWireState getCurrentState();
		std::string StateToString(FireWireState inState);
	private:
		//Thread Classes
		boost::thread *mainThread_;
		std::queue<FireWireCommands> commandQ_;//holds all the commands 
					//image processing Queue
		std::queue<Frame> dcQ_;//

		//Locks
		boost::shared_mutex mutex_commandQ_;
		boost::shared_mutex mutexTerminate_;
		boost::shared_mutex mutexState_;
			//thread status locks
		boost::shared_mutex mutex_runningDC1394_;
		boost::shared_mutex mutex_runningDebayer_;
				//image processing Locks
		boost::shared_mutex mutex_dcQ_;
		boost::shared_mutex mutex_debayerQ_;

		
		//internal States
		bool Terminate_;
		bool dc1394Running_;//indicates which threads are alive
		bool debayerRunning_;
		
		std::string leftDir_;
		std::string rightDir_;
		
		void processCommandQ();
		std::shared_ptr<spdlog::logger> oLog;
		FireWireState currentState_;
		FireWireSettings cameraConfig_;
		/////////////////////
		////bumblebee related functions
		//////////////////
		bool InitializeDC1394();
		void closeCamera();
		bool UpdateSettings();
		//////BumbleBee and LIBDC1394 global Classes 
		///////////////////////////////
		dc1394_t * init_1394_;//is the camera properly set up
		dc1394camera_t *camera_;//reference to camera

		//Thread Functions
		void mainLoop();
		void getDC1394Frame();
		void debayerFrame();
		void waitThreads();

		
};
	
}

#endif