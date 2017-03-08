#ifndef DETECTOR_BASE_SETTINGS_HPP
#define DETECTOR_BASE_SETTINGS_HPP

#include <opencv2/features2d.hpp>

namespace stereo
{
	
class DetSettings
{
	public:
			DetSettings();
			virtual void increment();
			virtual void decrement();
			virtual void setStaticSettings();
			virtual void setInternalSettings();
			void setAdjustSettings(float l_rate);
			virtual void getFeatures(cv::Mat image, std::vector<cv::KeyPoint> &output);
	protected:
		float learning_rate_;
};

}
#endif