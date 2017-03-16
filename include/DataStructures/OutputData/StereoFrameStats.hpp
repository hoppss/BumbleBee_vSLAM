#ifndef STEREO_FRAME_STATS_HEADER_HPP
#define STEREO_FRAME_STATS_HEADER_HPP
#include <chrono>

#include "DataStructures/OutputData/StereoKP.hpp"
namespace stereo
{
class StereoFrameStats
{	
	public:
	 StereoFrameStats();
	 std::vector<cv::KeyPoint> l_preEmptiveRejected_;
	 std::vector<cv::KeyPoint> r_preEmptiveRejected_;	 
	 std::vector<StereoKP> outliers_;
};

}
#endif