#ifndef WINDOW_INTERNAL_HEADER_SETTINGS_HPP
#define WINDOW_INTERNAL_HEADER_SETTINGS_HPP

#include "DataStructures/OutputData/StereoFrame.hpp"

namespace stereo

{
	

class WindowInternal
{
	protected:
		bool bootstrapped_;
	public:
		enum WindowMatch
		{
			SIMPLE_WINDOW=1<<0,
			BRUTE_FORCE=1<<1,
			RADIUS=1<<2,
			KNN_MATCH=1<<3,
			DATABASE=1<<4,
			LEFT_ONLY=1<<5,
		};
		enum WindowDescription
		{
			BRIEF_DESCR=1<<0
		};
		enum ComputeStatistics
		{
			SINGLE_FRAME_ADDITION_TIME=1<<0,//overall time taken to add a single frame
			MATCHING_TIME=1<<2,
		};
		enum RobustnessCriteria
		{
			SINGLE_MOTION_RANSAC=1<<0,
			THRESHOLD_REJECTION=1<<1,
		};
		WindowInternal();
		int w_width_;//how many frames to keep
		float match_thresh_;
		int getScoreMeasure();
		WindowDescription internalDescription_;
		ComputeStatistics internalStatistics_;
		RobustnessCriteria internalRobustness_;
		WindowMatch internalMatch_;
		
};
}

#endif