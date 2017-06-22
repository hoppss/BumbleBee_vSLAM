#ifndef BUMBLE_FRAME_HEADER_HPP
#define BUMBLE_FRAME_HEADER_HPP

#include "DataStructures/DataSet/ImageMetaData.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace stereo
{
	

	
class BumbleFrame
{
	public:
		ImageMetaData Meta_;
		void getBothImages(cv::Mat &output);
		void getLeftImage(cv::Mat &output);
		void getRightImage(cv::Mat &output);
		BumbleFrame();
};

}
	


#endif
