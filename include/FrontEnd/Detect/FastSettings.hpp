#ifndef DETECT_FAST_SETTINGS_HEADER_HPP
#define DETECT_FAST_SETTINGS_HEADER_HPP

#include <opencv2/features2d.hpp>

namespace stereo
{

class FastSettings
{
	public:
		int threshold_;
		bool nonmaxSuppression_;
		int neighbourType_;
		FastSettings();
};
	
	
}

#endif