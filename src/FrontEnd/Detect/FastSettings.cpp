#include "FrontEnd/Detect/FastSettings.hpp"

namespace stereo {

FastSettings::FastSettings()
{
	threshold_=10;
	nonmaxSuppression_=false;
	neighbourType_=cv::FastFeatureDetector::TYPE_9_16;
}
	
	
}