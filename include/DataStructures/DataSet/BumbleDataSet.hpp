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
		std::vector<BumbleFrame>::iterator current_frame_;
		int delayTime=1000/15;
		/*----------------
		 * DataSet input variables
		 * --------------*/
		std::string rootDir_;
		std::string leftDir_,rightDir_;
		void populateFrameList();
		std::vector<std::string> getFilesList(std::string dir);
		std::vector<std::string> getDirList(std::string dir);
		std::vector<BumbleFrame> frameReferences_;
		//TODO get times between frames
	public:
		BumbleDataSet(std::string root);
		cv::Mat getCurrent();
		cv::Mat getCurrentLeft();
		cv::Mat getCurrentRight();
		bool incrementFrame();
		bool decrementFrame();
};

	
	
}

#endif