
#include "DataStructures/DataSet/BumbleFrame.hpp"
namespace stereo
{

BumbleFrame::BumbleFrame()
{
	//take left file name
	
}

void BumbleFrame::getBothImages(cv::Mat& output)
{
	cv::imread(Meta_.fullDir_, CV_LOAD_IMAGE_GRAYSCALE).copyTo(output);
}


void BumbleFrame::getLeftImage(cv::Mat& output)
{
	cv::Mat both;
	getBothImages(both);
	
	both(cv::Rect(0,768,1024,768)).copyTo(output);
}

void BumbleFrame::getRightImage(cv::Mat& output)
{
	cv::Mat both;
	getBothImages(both);
	
	both(cv::Rect(0,0,1024,768)).copyTo(output);
}


	
}