#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

namespace stereo{

StereoFeatures::StereoFeatures()
{

}



void StereoFeatures::GetFeatures(cv::Mat image, std::vector< cv::KeyPoint >& output,StereoInternal settings_)
{
	settings_.detector_->getFeatures(image,output);
}

}