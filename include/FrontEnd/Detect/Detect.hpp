#ifndef DETECT_ALGORITHM_HEADER_HPP
#define DETECT_ALGORITHM_HEADER_HPP

#include "FrontEnd/Detect/FastSettings.hpp"
#include <opencv2/features2d/features2d.hpp>

namespace stereo
{
	
void detectFast(cv::Mat image,FastSettings inSettings_,std::vector<cv::KeyPoint> &outputKP);	
	
	
}

#endif