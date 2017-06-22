#include "Manager/PsuedoManager.hpp"
#include "DataStructures/DataSet/BumbleDataSet.hpp"

#include <iostream>

int main(int argc, char * argv[])
{
	using namespace stereo;
	
	PsuedoManager a("/media/kakashi/recording-19700101-020319-856");

	/*cv::Mat img,RGBImage;
	img=cv::imread("/media/kakashi/recording-19700101-020319-856/19700101-020319-856.ppm",CV_LOAD_IMAGE_UNCHANGED);

	cv::cvtColor(img, RGBImage, CV_BayerBG2GRAY);
	cv::namedWindow("a",cv::WINDOW_NORMAL);
	cv::imshow("a",RGBImage);
	cv::waitKey(0);*/
	return 0;
}
