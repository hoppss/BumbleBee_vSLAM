#ifndef PSUEDO_REAL_TIME_MANAGER
#define PSUEDO_REAL_TIME_MANAGER

#include <iostream>
#include "DataStructures/DataSet/BumbleDataSet.hpp"

namespace stereo
{
	
class PsuedoManager
{
	private:
		BumbleDataSet *ptrData_;
		std::string rootDir_;
	public:
		PsuedoManager(std::string rootDir);
};
	
}

#endif