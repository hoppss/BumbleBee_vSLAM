#ifndef STEREO_FRAME_HEADER_HPP
#define STEREO_FRAME_HEADER_HPP

#include "DataStructures/OutputData/StereoFrameStats.hpp"
#include "DataStructures/OutputData/StereoKP.hpp"

namespace stereo{

class StereoFrame
{
	public:
		StereoFrame();
		std::vector<cv::KeyPoint> leftKP_,rightKP_;
		cv::Mat leftDescrip_,rightDescrip_;
		std::vector<cv::DMatch> matches_;
		StereoFrameStats statistics_;
		std::vector<StereoKP> outKP_;
		//TODO Timings
};
}

#endif