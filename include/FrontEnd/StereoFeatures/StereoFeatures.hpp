#ifndef STEREO_FEATURES_HEADER_HPP
#define STEREO_FEATURES_HEADER_HPP

#include "FrontEnd/Detection/Detection.hpp"
#include "DataStructures/OutputData/OutputData.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <FrontEnd/StereoFeatures/StereoInternal.hpp>
#include <iostream>

namespace stereo
{
class StereoFeatures
{
	private:
	public:
		StereoFeatures();
		void GetFeatures(cv::Mat image,std::vector<cv::KeyPoint> &output,StereoInternal settings_);
		void getFrame(StereoFrame &outputFrame);

};
	
}

#endif