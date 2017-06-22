#ifndef BUMBLE_DATASET_HEADER_HPP
#define BUMBLE_DATASET_HEADER_HPP

#include <iostream>
#include <queue>
#include <boost/filesystem.hpp>
#include <string.h>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include "DataStructures/DataSet/BumbleFrame.hpp"

namespace stereo
{
	
class BumbleDataSet
{
	private:
		/*--------------
		 * Playback variables
		 * --------------*/
		int delayTime=500;
		std::vector<BumbleFrame>::iterator currentFrame_;
		/*----------------
		 * DataSet input variables
		 * --------------*/
		std::string rootDir_;
		std::string leftDir_,rightDir_;
		void populateFrameList();
		std::vector<std::string> getFilesList(std::string dir);
		std::vector<std::string> getDirList(std::string dir);
		std::vector<BumbleFrame> frameReferences_;
	public:
		BumbleDataSet(std::string root);
		void playback();
};

	
	
}

#endif