#include "FrontEnd/Detection/DetSettings.hpp"

namespace stereo
{
DetSettings::DetSettings()
{
	
}

void DetSettings::decrement()
{

}

void DetSettings::increment()
{

}

void DetSettings::setInternalSettings()
{

}

void DetSettings::setStaticSettings()
{

}

void DetSettings::setAdjustSettings(float l_rate)
{
	learning_rate_=l_rate;
}


void DetSettings::getFeatures(cv::Mat image, std::vector< cv::KeyPoint >& output)
{

}




	
	
}