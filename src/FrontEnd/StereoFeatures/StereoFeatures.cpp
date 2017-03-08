#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

namespace stereo{

StereoFeatures::StereoFeatures()
{
	initialized_=false;
}

void StereoFeatures::setConfiguration(Stereo configuration)
{
	initialized_=true;
	calibration_=configuration;
}


void StereoFeatures::setConfiguration(std::string directory)
{
	cv::FileStorage fs(directory,cv::FileStorage::READ);
	fs["stereocalibration"]>>calibration_;
	fs.release();
	initialized_=true;
}


StereoFeatures::StereoFeatures(std::string directory)
{
	setConfiguration(directory);
}

StereoFeatures::StereoFeatures(Stereo configuration)
{
	initialized_=true;
	calibration_=configuration;
}


	
}