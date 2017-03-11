#ifndef STEREO_FEATURES_HEADER_HPP
#define STEREO_FEATURES_HEADER_HPP

#include "FrontEnd/Detection/Detection.hpp"
#include "DataStructures/OutputData/OutputData.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <FrontEnd/StereoFeatures/StereoInternal.hpp>
#include <iostream>
#include <algorithm>

namespace stereo
{
class StereoFeatures
{
	private:
		void preEmptiveRejection(StereoFrame &prunedFrame,cv::Mat fundamental);
		void postRejection(StereoFrame &prunedFrame,cv::Mat fundamental);
	public:
		StereoFeatures();
		float getFundamentalError(cv::KeyPoint left,cv::KeyPoint right,cv::Mat fundamental);
		void getTopFeatures(std::vector<cv::KeyPoint> &output,int maxFeatures);
		void SimpleFeatures(cv::Mat image,std::vector<cv::KeyPoint> &output,StereoInternal settings_);
		void getFrame(StereoFrame &outputFrame,cv::Mat LeftIn,cv::Mat RightIn,StereoInternal settings_);
		void imageRectification(cv::Mat left,cv::Mat right,cv::Mat &outLeft,cv::Mat &outRight,bool StereoRect);
		//TODO RANSAC rejection
};
	
}

#endif