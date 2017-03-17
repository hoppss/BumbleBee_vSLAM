#ifndef DETECTOR_BASE_SETTINGS_HPP
#define DETECTOR_BASE_SETTINGS_HPP

#include <opencv2/features2d.hpp>

namespace stereo
{
	
class DetSettings
{
	public:
			DetSettings();
			virtual bool increment();
			virtual bool decrement();
			virtual void setStaticSettings();
			virtual void setInternalSettings();
			virtual	void setInternalSettings(int threshold,int octaves,int scale);//BRISK
			virtual void setBounds(int min_t,int max_t,int min_oct,int max_oct);//BRISK
			virtual void setAdjustSettings(float l_rate,int min_step);
			virtual void getFeatures(cv::Mat image, std::vector<cv::KeyPoint> &output);
			virtual void setBounds();
	protected:
		float learning_rate_;
		int minimum_step_;
		bool stagnant_;
};

}
#endif