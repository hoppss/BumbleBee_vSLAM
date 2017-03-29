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
	public:
		StereoRectifiedFeedback();
		StereoRectifiedFeedback(StereoRect *ptr);
		/*get functions -> create and return images with no display functionality*/
		void getOriginalDetected(StereoFrameStats &debug,cv::Mat &lout,cv::Mat &rout);
		void getRectDetected(StereoFrame &output,StereoFrameStats &debug,cv::Mat &lout,cv::Mat &rout);
		void getRectifiedMatches(StereoFrameStats &debug,StereoFrame &out,cv::Mat &outImage);
		void getSingleRect(cv::Mat in,cv::Mat &out,bool left);
		void getSideSideRect(cv::Mat limg,cv::Mat rimg,cv::Mat &out);
		void getSideBySide(cv::Mat left,cv::Mat right,cv::Mat &out);//must be the same size and type
		/*draw-> assume images already exist, and they simply draw over them*/
		void drawInlierMatches(cv::Mat &inputOutput,StereoFrame &out,cv::Scalar col);
		void drawEpiRejections(cv::Mat &inputOutput,StereoFrameStats &debug,cv::Scalar col);
		void drawEpiRejections(cv::Mat &inputOutput,StereoFrameStats &debug,cv::Scalar col,cv::Scalar colDist);

};
	
	
}
#endif