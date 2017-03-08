
#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"


int main(int argc, char * argv[])
{
/*	stereo::DetSettings *ptr_brisk;
	ptr_brisk= new stereo::BRISKdet();
	
	cv::Mat testImage;
	
	testImage=cv::imread("/home/ubuntu/l.jpg",cv::IMREAD_GRAYSCALE);
	
	ptr_brisk->setAdjustSettings(22);
	std::vector<cv::KeyPoint> test;
	
	ptr_brisk->getFeatures(testImage,test);
	
	std::cout<<test.size();*/

	stereo::StereoFeatures bumbleBee("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");
	
	
	return 0;
}