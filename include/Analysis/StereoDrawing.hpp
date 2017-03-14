#ifndef STEREO_DRAWING_HEADER_HPP
#define STEREO_DRAWING_HEADER_HPP

#include "DataStructures/CameraInfo/Stereo.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgproc.hpp"

namespace stereo
{
	
class StereoDrawing
{
	public:
		Stereo config_;
		StereoDrawing();
		StereoDrawing(Stereo con);
		StereoDrawing(std::string dir);
		void drawEpiLine();
		void stereoRectify(cv::Mat input,cv::Mat &output,bool leftImage,bool includeDistortion);
		void drawROI(cv::Mat input,bool left,bool includeDistortion);
		void drawROI(cv::Mat input,cv::Mat &output,bool display,bool left,bool includeDistortion);
		void drawStereoEpi(cv::Mat left,cv::Mat right, cv::Mat &output,bool withROI);
};
	
}

#endif