#ifndef STEREO_RECTIFIED_FEEDBACK_HEADER_HPP
#define STEREO_RECTIFIED_FEEDBACK_HEADER_HPP
#include "DataStructures/CameraInfo/StereoRect.hpp"

namespace stereo
{
	
class StereoRectifiedFeedback
{
	private:
		StereoRect *ptr_cal;
	public:
		StereoRectifiedFeedback();
		StereoRectifiedFeedback(StereoRect *ptr);
};
	
	
}
#endif