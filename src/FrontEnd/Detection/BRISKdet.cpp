#include "FrontEnd/Detection/BRISKdet.hpp"

namespace stereo{
BRISKdet::BRISKdet() : DetSettings()
{
	threshold_=30;
	octaves_=3;
	pattern_scale_=1.0;
}

void BRISKdet::decrement()
{

}

void BRISKdet::increment()
{

}

void BRISKdet::setInternalSettings(int threshold, int octaves, int scale)
{
	threshold_=threshold;
	octaves_=octaves;
	pattern_scale_=scale;
}


void BRISKdet::getFeatures(cv::Mat image, std::vector< cv::KeyPoint >& output)
{
	cv::BRISK det(threshold_,octaves_,pattern_scale_);
	det.detect(image,output);
}





}