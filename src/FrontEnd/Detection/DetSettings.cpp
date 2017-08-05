#include "FrontEnd/Detection/DetSettings.hpp"

namespace stereo
{
DetSettings::DetSettings()
{
	stagnant_=false;
	learning_rate_=0.1;
	minimum_step_=1;
}

bool DetSettings::decrement()
{
	return false;//always send stop flag since it has not been properly initialized
}

bool DetSettings::increment()
{
	return false;
}

void DetSettings::setInternalSettings()
{

}

void DetSettings::setStaticSettings()
{

}

void DetSettings::setAdjustSettings(float l_rate,int min_step)
{
}


void DetSettings::getFeatures(cv::Mat image, std::vector< cv::KeyPoint >& output)
{

}

void DetSettings::setBounds()
{

}


void DetSettings::setBounds(int min_t, int max_t, int min_oct, int max_oct)
{

}


void DetSettings::setInternalSettings(int threshold, int octaves, int scale)
{

}


std::string DetSettings::getStringName()
{

}



	
	
}