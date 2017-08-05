#include "FrontEnd/Detection/BRISKdet.hpp"

namespace stereo{
BRISKdet::BRISKdet() : DetSettings()
{
	threshold_=30;
	octaves_=3;
	pattern_scale_=1.1;
	min_thresh_=1;
	max_thresh_=250;
	min_octaves_=2;
	max_octaves_=8;
	newStep();
}

bool BRISKdet::decrement()
{
	int update;
	update=threshold_-update_step_;
	if(update<min_thresh_)
	{
		return false;
	}
	else
	{
		threshold_=update;
		return true;
	}
}

bool BRISKdet::increment()
{
	int update;
	update=threshold_+update_step_;
	if(update>max_thresh_)
	{
		return false;
	}
	else
	{
		threshold_=update;
		return true;
	}
	
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


void BRISKdet::setBounds(int min_t, int max_t, int min_oct, int max_oct)
{
	min_thresh_=min_t;
	max_thresh_=max_t;
	min_octaves_=min_oct;
	max_octaves_=max_oct;
	newStep();
}


void BRISKdet::newStep()
{
		int step=(max_thresh_-min_thresh_)*learning_rate_;
		if(step<minimum_step_)
		{
			update_step_=minimum_step_;
		}
		else
		{
			update_step_=step;
		}
}


void BRISKdet::setAdjustSettings(float l_rate, int min_step)
{
	learning_rate_=l_rate;
	minimum_step_=min_step;
}


std::string BRISKdet::getStringName()
{
	std::stringstream outName;
	outName.str("");
	outName<<"BRISK_DET_"<<threshold_<<"__"<<octaves_<<"__"<<pattern_scale_;
	return outName.str();
}




}