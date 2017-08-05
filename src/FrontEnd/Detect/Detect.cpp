#include "FrontEnd/Detect/Detect.hpp"

namespace stereo {

void detectFast(cv::Mat image,FastSettings inSettings_, std::vector< cv::KeyPoint >& outputKP)
{
	cv::FASTX(image,outputKP,inSettings_.threshold_,inSettings_.nonmaxSuppression_,inSettings_.neighbourType_);
}
	
	
}