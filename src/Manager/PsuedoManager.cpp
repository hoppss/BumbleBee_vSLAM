#include "Manager/PsuedoManager.hpp"

namespace stereo 
{

PsuedoManager::PsuedoManager(std::string rootDir)
{
	rootDir_=rootDir;
  ptrData_=new BumbleDataSet(rootDir_);
	ptrData_->playback();
}


}