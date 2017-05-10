#ifndef FRAME_HEADER_HPP_
#define FRAME_HEADER_HPP_

#include <opencv2/core.hpp>
#include <string.h>

namespace stereo
{

class Frame
{
	public:
		cv::Mat image_;
		std::string fullDir_;
		Frame();
};
	
}

#endif