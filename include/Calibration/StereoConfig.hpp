#ifndef STEREO_CONFIG_HEADER_HPP
#define STEREO_CONFIG_HEADER_HPP

#include "Calibration/SingleOutput.hpp"

namespace stereo
{
class StereoConfig
{
	public:
		StereoConfig();
		SingleConfig config_left_,config_right_;
		SingleOutput output_left_,output_right_;
		bool showIndividualMatches_;
		bool debugInfo_;
		bool compute_rectify_;
		bool compute_left_;
		bool compute_right_;
};
	
}

#endif