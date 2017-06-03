#ifndef BUMBLE_DATASET_HEADER_HPP
#define BUMBLE_DATASET_HEADER_HPP

#include <iostream>
#include <queue>
#include <boost/filesystem.hpp>
#include <string.h>
#include <algorithm>

#include "DataStructures/DataSet/BumbleFrame.hpp"

namespace stereo
{
	
class BumbleDataSet
{
	private:
		std::string rootDir_;
		std::string leftDir_,rightDir_;
		void populateFrameList();
		std::vector<std::string> getFilesList(std::string dir);
		std::vector<std::string> getDirList(std::string dir);
		std::vector<BumbleFrame> frameReferences_;
	public:
		BumbleDataSet(std::string root);
};
	
	
}

#endif