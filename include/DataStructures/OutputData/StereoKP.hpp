#ifndef STEREO_KEYPOINT_HEADER_HPP
#define STEREO_KEYPOINT_HEADER_HPP

#include "opencv2/features2d.hpp"

namespace stereo
{
class StereoKP
{
	public:
		StereoKP();
		cv::Mat leftDescr,rightDescr;
		float matchScore;
		cv::KeyPoint left,right;
};
	
}

#endif