#ifndef FIREWIRE_MANAGER_HEADER_HPP
#define FIREWIRE_MANAGER_HEADER_HPP





/////////////////////
///////Camera related Includes
#include "Manager/FireWireSettings.hpp"
////////////////////////
////////////////////
#include <iostream>

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
			Record=1,
			Stop=2,
		};
		
		//Initializing -> still configuring LIBDC1394 + checking settings
		// when it is completed initializing, it will enter the waiting state, otherwise it will enter
		//the FAILED State
		
		//Waiting -> Manager exists but is currently doing no Work
		//Recording-> All threads running
		
		enum FireWireState
		{
			Initializing=0,
			Waiting=1,
			Recording=2,
			Closing=3,
			FAILED=4,
		};
		FireWireManager(std::string configDir,std::string logDir);//includes XMl firewire settings directory
		FireWireManager(std::string logDir);//just the full directory to Log
		//external interfaces
		void SendCommand(FireWireCommands command);
		FireWireState getCurrentState();
	private:
		//Thread Classes
		boost::thread *mainThread_;
		std::queue<FireWireCommands> commandQ_;//holds all the commands 
					//image processing Threads
		
		//Locks
		boost::shared_mutex mutex_commandQ_;
		boost::shared_mutex mutexTerminate_;
		boost::shared_mutex mutexState_;
				//image processing Locks
		
		
		//internal States
		std::shared_ptr<spdlog::logger> oLog;
		FireWireState currentState_;
		FireWireSettings cameraConfig_;
		/////////////////////
		////bumblebee related functions
		///////////////////

		bool InitializeDC1394();
		bool UpdateSettings();
		
		//////BumbleBeeSettings
		dc1394_t * init_1394;//is the camera properly set up
		dc1394camera_t *camera;//reference to camera

		bool Terminate_;
		void processCommandQ();
		//Thread Functions
		void mainLoop();

		
};
	
}

#endif