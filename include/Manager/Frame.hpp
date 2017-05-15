#ifndef FRAME_HEADER_HPP_
#define FRAME_HEADER_HPP_

#include <opencv2/core.hpp>
#include <string.h>

namespace stereo
{

class Frame
{
	public:
		cv::Mat outputImage=cv::Mat(1536,1024,CV_8UC1);
		uint64_t tstamp_;
		Frame();
};
	
}

#endif