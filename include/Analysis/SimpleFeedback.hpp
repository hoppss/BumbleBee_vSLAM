#ifndef SIMPLE_FEEDBACK_HEADER_HPP
#define SIMPLE_FEEDBACK_HEADER_HPP
#include "DataStructures/OutputData/StereoFrame.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"


namespace stereo
{
class SimpleFeedback
{
	private:
		bool checkInlier(cv::Point2f);
	public:
		SimpleFeedback();
		void displayMatches();
		void displayOutliers();
		void displayEpiLines();
};
	
}

#endif