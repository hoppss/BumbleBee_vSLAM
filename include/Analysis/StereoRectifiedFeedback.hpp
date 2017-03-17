#ifndef STEREO_RECTIFIED_FEEDBACK_HEADER_HPP
#define STEREO_RECTIFIED_FEEDBACK_HEADER_HPP
#include "DataStructures/CameraInfo/StereoRect.hpp"
#include "DataStructures/OutputData/StereoFrame.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

namespace stereo
{
	
class StereoRectifiedFeedback
{
	private:
		StereoRect *feed_cal;
		void drawStereoKP(StereoKP in,cv::Mat &inputOutput,cv::Scalar col);
		void drawStereoKP(StereoKP in,cv::Mat &inputOutput,cv::Scalar col,cv::Scalar col2);
	public:
		StereoRectifiedFeedback();
		StereoRectifiedFeedback(StereoRect *ptr);
		void RectifyImg(cv::Mat limg,cv::Mat rimg,cv::Mat &out);
		void RectifyImg(cv::Mat in,cv::Mat &out,bool left);
		void sideBySide(cv::Mat left,cv::Mat right,cv::Mat &out);//must be the same size and type
		void displayRectifiedMatches(cv::Mat lrect,cv::Mat rrect,StereoFrame out);
		void drawInliers(cv::Mat &inputOutput,StereoFrame &out,cv::Scalar col);
		void drawInliers(cv::Mat &inputOutput,StereoFrame &out,cv::Scalar col,cv::Scalar col2);
		void drawOutliers(cv::Mat &inputOutput,StereoFrame &out,cv::Scalar col);
		void drawOutliers(cv::Mat &inputOutput,StereoFrame &out,cv::Scalar col,cv::Scalar col2);
		void showInlierOutlier(cv::Mat lIn,cv::Mat rIn,StereoFrame out);
		void showInlier(cv::Mat lIn,cv::Mat rIn, StereoFrame out);
		void drawEpiLines(cv::Mat &inputOutput,int total);

};
	
	
}
#endif