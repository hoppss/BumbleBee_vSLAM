#ifndef PSUEDO_REAL_TIME_MANAGER
#define PSUEDO_REAL_TIME_MANAGER

#include <iostream>
#include <queue>
#include <boost/filesystem.hpp>

namespace stereo
{
	
class PsuedoManager
{
	private:
		std::queue<int> frameSeq_;//
		std::string rootDir_;
		std::string leftDir_,rightDir_;
		boost::filesystem::path *inputDir_;//root directory of video sequence
		//utilities
		std::vector<std::string> getFilesList(std::string dir);
		void populateFrameList();
	public:
		PsuedoManager(std::string rootDir);
};
	
}

#endif