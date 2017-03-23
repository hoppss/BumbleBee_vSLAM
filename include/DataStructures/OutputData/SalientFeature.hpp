#ifndef SALIENT_FEATURE_HEADER_HPP
#define SALIENT_FEATURE_HEADER_HPP

#include "DataStructures/OutputData/StereoKP.hpp"
/* internal class that keeps track of a unique visually salient feature,
 */ 
namespace stereo
{

class SalientFeature
{
	public:
		SalientFeature();
		std::vector<int> frameSeen_;//frame index relative to  window
		std::vector<StereoKP> correspondences_;
};
	
	
}

#endif