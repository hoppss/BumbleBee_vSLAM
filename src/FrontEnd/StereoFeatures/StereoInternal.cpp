#include "FrontEnd/StereoFeatures/StereoInternal.hpp"

namespace stereo
{

StereoInternal::StereoInternal()
{
	maxRadius_=10.0;
	initialized_=false;
}

void StereoInternal::setCameraInfo(Stereo configuration)
{
	initialized_=true;
	calibration_=configuration;
}


void StereoInternal::setCameraInfo(std::string configuration_xml)
{
	cv::FileStorage fs(configuration_xml,cv::FileStorage::READ);
	fs["stereocalibration"]>>calibration_;
	fs.release();
	initialized_=true;
}

int StereoInternal::getScoreMeasure()
{
	int Ans;
	switch(internalDescription_)
	{
		case BRIEF_DESCR :
		{
			Ans=cv::NORM_HAMMING;
			break;
		}
	}
	return Ans;
}


	
}