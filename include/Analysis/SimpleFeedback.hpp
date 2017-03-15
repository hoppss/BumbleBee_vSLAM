#ifndef SIMPLE_FEEDBACK_HEADER_HPP
#define SIMPLE_FEEDBACK_HEADER_HPP
#include "DataStructures/OutputData/StereoFrame.hpp"
#include "DataStructures/Transforms/Isometry.hpp"
#include "Analysis/StereoDrawing.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"


namespace stereo
{
class SimpleFeedback
{
	private:
	public:
		cv::Mat UintMapx_,UintMapy_;//fixed point rectification map
		cv::Mat L_fMapx_,L_fMapy_;//float rectification map
		cv::Mat R_fMapx_,R_fMapy_;
		cv::Mat Qmap_;
		cv::Mat P_l_,P_r_;//ideal projection matrices
		cv::Rect l_ROI_,r_ROI_;
		Isometry lIso_,lrectIso_;
		Isometry rIso_,rrectIso_;
		SimpleFeedback();
		void displayMatches();
		void displayOutliers();
		void displayEpiLines();
};
	
}

#endif