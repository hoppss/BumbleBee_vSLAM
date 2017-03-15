#include "Analysis/StereoRectifiedFeedback.hpp"

namespace stereo
{
	
StereoRectifiedFeedback::StereoRectifiedFeedback()
{

}


StereoRectifiedFeedback::StereoRectifiedFeedback(StereoRect* ptr)
{
	ptr_cal=ptr;//NOTE there is no deep copying here, assumes the object stereoRect still exists in memory
}

	
}