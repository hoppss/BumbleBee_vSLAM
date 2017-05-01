#ifndef FIREWIRE_MANAGER_HEADER_HPP
#define FIREWIRE_MANAGER_HEADER_HPP

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
	private:
		//Thread Classes
		boost::thread *mainThread_;
		std::queue<char> commandQ_;
					//image processing Threads
		
		//Locks
		boost::shared_mutex mutex_commandQ_;
		boost::shared_mutex mutexTerminate_;
				//image processing Locks
		
		
		//internal States
		std::shared_ptr<spdlog::logger> oLog;
		bool Terminate_;
		bool Initialized_;//true if no errors during initializing
		void processCommandQ();
		//Thread Functions
		void mainLoop();
	public:
		enum FireWireCommands
		{
			Initialize,
			Record,
			Stop,
			Close,
		};
		enum FireWireState
		{
			Initializing,
			Recording,
			Closing,
			FAILED,
		};
		FireWireManager(std::string configDir,std::string logDir);//includes XMl firewire settings directory
		FireWireManager(std::string logDir);//just the full directory to Log
		//external interfaces
		void SendCommand(FireWireCommands command);
		
};
	
}

#endif