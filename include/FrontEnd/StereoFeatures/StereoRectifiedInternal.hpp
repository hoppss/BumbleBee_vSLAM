#ifndef STEREO_RECTIFIED_INTERNAL_HEADER_HPP
#define STEREO_RECTIFIED_INTERNAL_HEADER_HPP_

#include "FrontEnd/StereoFeatures/StereoInternal.hpp"
#include "DataStructures/CameraInfo/StereoRect.hpp"

/**
 * Holds all of the stereo internal settings such as robustness checks to apply,
 * match methods, etc..
 this particular class assumes a full stereo rectification with distortion is needed
 and as such computes and copies only the required information from Stereo*/
namespace stereo
{

class StereoRectifiedInternal : public StereoInternal
{
	public:
		StereoRect *ptr_cal_;
		StereoRectifiedInternal();
		~StereoRectifiedInternal();
	protected:
		bool LoadCameraSettings(std::string dir);
		bool LoadCameraSettings(Stereo conf);
};

}


#endif