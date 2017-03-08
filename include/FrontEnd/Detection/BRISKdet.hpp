#ifndef BRISK_SETTINGS_HEADER_HPP
#define BRISK_SETTINGS_HEADER_HPP
#include "FrontEnd/Detection/DetSettings.hpp"
#include <stdio.h>
#include <iostream>



namespace stereo{

class BRISKdet: public DetSettings
{
	private:
		int threshold_;
		int octaves_;
		float pattern_scale_;
	public:
		BRISKdet();
		void setInternalSettings(int threshold,int octaves,int scale);
		void increment();
		void decrement();
		void getFeatures(cv::Mat image, std::vector<cv::KeyPoint> &output);
};
	
}
#endif