#include "Manager/FireWireManager.hpp"

namespace stereo {

FireWireManager::FireWireManager(std::string configDir, std::string logDir)
{
	currentState_=Initializing;
	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
}


FireWireManager::FireWireManager(std::string logDir)
{
	currentState_=Initializing;
	oLog=spdlog::basic_logger_mt("FireWireManager", logDir);
	oLog->set_pattern("[%H:%M:%S:%e] [thread %t] %v ");
	
	mainThread_= new boost::thread(&FireWireManager::mainLoop,this);
	
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
				WriteLock stateWLock(mutexState_);
				if(currentState_&Waiting)
				{
					currentState_=Recording;
					oLog->info("Recording State Set");
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




///////////////////
//Thread functions
//////////////////


void FireWireManager::mainLoop()
{
	oLog->info("FireWireManager initialized");
	oLog->info("entered Main Loop");
	bool killLoop=false;
	/////////////////////////
	///try update 
	
	
	
	currentState_=Waiting;
	
	while(!killLoop)
	{
		processCommandQ();
		ReadLock an(mutexState_);
		if(currentState_&Recording)
		{
			oLog->info("in Recording State");
		}
		if(currentState_&Closing)
		{
			oLog->info("in Closing State");
			killLoop=true;
		}
		
		usleep(1000);
	}
	oLog->info("main loop killed");
	
}




////////////////////
////BumbleBee Related Functions
/////////////////


bool FireWireManager::InitializeDC1394()
{
	
}

bool FireWireManager::UpdateSettings()
{
	if(!init_1394)
	{
		oLog->critical("Update Settings Failed to take hold as DC1394 has not been initiated");
		return false;
	}
	//attempt to change all the settings at once with new values
	std::vector<dc1394error_t> basic_e,expose_e,balance_e,shutter_e,gain_e,bright_e;
	//holds results of each error code, if any of the vectors are a failure, immediate exit and return false
	cameraConfig_.setBasicSettings(basic_e,camera);
	if(cameraConfig_.checkUpdated(basic_e))
	{
		cameraConfig_.setBright(bright_e,camera);
		if(cameraConfig_.checkUpdated(bright_e))
		{
			cameraConfig_.setExposure(expose_e,camera);
			if(cameraConfig_.checkUpdated(expose_e))
			{
				cameraConfig_.setGain(gain_e,camera);
				if(cameraConfig_.checkUpdated(gain_e))
				{
					cameraConfig_.setShutter(shutter_e,camera);
					if(cameraConfig_.checkUpdated(shutter_e))
					{
						cameraConfig_.setWBalance(balance_e,camera);
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