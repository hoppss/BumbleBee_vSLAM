#include "Manager/FWmanager.hpp"
namespace stereo
{
	
FWmanager::FWmanager()
{

}


void FWmanager::singleDisplay()
{
	cv::Mat leftImage,rightImage;
	bumbleBee_.singleCapture(leftImage,rightImage);
	
	
	StereoFeatures det;
	StereoFrame myFrame;
	
	det.getFrame(myFrame,leftImage,rightImage,FrontEnd_config);
	
	cv::Mat outImage;
	cv::drawMatches(leftImage,myFrame.leftKP_,
									rightImage,myFrame.rightKP_,
								  myFrame.matches_,outImage);
	cv::namedWindow("out",cv::WINDOW_NORMAL);
	cv::imshow("out",outImage);
	cv::waitKey(0);
	cv::destroyWindow("out");
}


}