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
		int min_thresh_,max_thresh_;
		int min_octaves_,max_octaves_;
		int update_step_;
		void newStep();
	public:
		BRISKdet();
		void setInternalSettings(int threshold,int octaves,int scale);
		void setBounds(int min_t,int max_t,int min_oct,int max_oct);
		void setAdjustSettings(float l_rate,int min_step);
		bool increment(); //decrement parameters
		bool decrement();
		void getFeatures(cv::Mat image, std::vector<cv::KeyPoint> &output);
};
	
}
#endif