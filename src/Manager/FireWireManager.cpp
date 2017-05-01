#include "Manager/FireWireManager.hpp"

namespace stereo {

FireWireManager::FireWireManager(std::string configDir, std::string logDir)
{
	Initialized_=false;
	
	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
}


FireWireManager::FireWireManager(std::string logDir)
{
	Initialized_=false;
	oLog=spdlog::basic_logger_mt("FireWireManager", logDir);
	oLog->set_pattern("[%H:%M:%S] [thread %t] %v ");
	

	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
	
}

//private
///////////internat states
void FireWireManager::processCommandQ()
{
	ReadLock comQLock(mutex_commandQ_);
	if(commandQ_.size()>0)
	{
		comQLock.unlock();
		WriteLock(mutex_commandQ_);
		
	}
	
	
}



//external interfaces
///////////////////

void FireWireManager::SendCommand(FireWireManager::FireWireCommands command)
{
	//add a command to the queue for processing in the mainThread
	WriteLock commandLock(mutex_commandQ_);
	//commandQ_.push()
	
	
	commandLock.unlock();

}


///////////////////
//Thread functions
//////////////////


void FireWireManager::mainLoop()
{
	Initialized_=true;
	oLog->info("FireWireManager initialized");
	oLog->info("entered Main Loop");
	bool killLoop=false;
	
	while(!killLoop)
	{
		oLog->info("looping");
		usleep(10000);
		
	}
	oLog->info("main loop killed");
	
}




}