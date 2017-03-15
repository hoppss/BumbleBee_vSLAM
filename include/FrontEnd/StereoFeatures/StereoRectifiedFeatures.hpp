#ifndef STEREO_RECTIFIED_FEATURES_HEADER_HPP
#define STEREO_RECTIFIED_FEATURES_HEADER_HPP
#include "FrontEnd/StereoFeatures/StereoRectifiedInternal.hpp"
#include "DataStructures/OutputData/StereoFrame.hpp"
#include "Analysis/StereoRectifiedFeedback.hpp"
#include <algorithm>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace stereo
{
class StereoRectifiedFeatures : public StereoRectifiedInternal

{
	public:
		StereoRectifiedFeatures();
		bool Initialize_(std::string directoryXML);
		bool checkSettings();
		void getFrame(StereoFrame &outputFrame,cv::Mat LeftIn,cv::Mat RightIn);
		void SimpleFrame(StereoFrame &outputFrame,cv::Mat LeftIn,cv::Mat RightIn);
		void pruneTopScores(std::vector< cv::KeyPoint >& output, int maxFeatures);
		void pruneTopScores(std::vector< cv::KeyPoint >& output,std::vector<cv::KeyPoint> &rejected, int maxFeatures);
		void getMatches(StereoFrame &outputFrame);
};
	
}

#endif