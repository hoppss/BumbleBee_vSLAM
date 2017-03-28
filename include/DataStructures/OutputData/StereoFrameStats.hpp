#ifndef STEREO_FRAME_STATS_HEADER_HPP
#define STEREO_FRAME_STATS_HEADER_HPP
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

namespace stereo
{
class StereoFrameStats
{	
	public:
			enum featureStats
		{
			DETECTION_TIME=1<<0,//overall
			CELL_DETECTION_TIME=1<<1,//for each grid cell
			DESCRIPTION_TIME=1<<2,
			CELL_DESCRIPTION_TIME=1<<3,
			OVERALL_TIME=1<<4,
			ADMIN_TIME=1<<5,//compute how much time is used switching into and out of functions
			KEEP_OUTLIER=1<<6, //save the features that were removed as outliers
			KEEP_PROGRESS=1<<7,
			KEEP_RECTIFIED=1<<8,
			KEEP_ROI_IMG=1<<9,
			KEEP_PRE_REJECTED=1<<10,
		};	
	 StereoFrameStats();
	 cv::Mat leftRect_,rightRect_;
	 cv::Mat leftROI_img_,rightROI_img_;
	 std::vector<cv::KeyPoint> l_preEmptiveRejected_;
	 std::vector<cv::KeyPoint> r_preEmptiveRejected_;	 
	 std::vector<cv::KeyPoint> epiOut_l,epiOut_r;
	 featureStats settings_;
	 bool checkSettings();
	 void setAllOn();

};

}
#endif