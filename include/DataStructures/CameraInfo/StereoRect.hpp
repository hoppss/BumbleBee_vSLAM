#ifndef STEREO_RECTIFIED_CAMERA_INFO_HEADER_
#define STEREO_RECTIFIED_CAMERA_INFO_HEADER_
#include "DataStructures/CameraInfo/Stereo.hpp"
/*only containing the essential information needed for a stereo rectified camera
 * configuration*/

namespace stereo
{

class StereoRect
{
	public:
		StereoRect(Stereo conf);
		cv::Mat UintMapx_,UintMapy_;//fixed point rectification map
		cv::Mat L_fMapx_,L_fMapy_;//float rectification map
		cv::Mat R_fMapx_,R_fMapy_;
		cv::Mat Qmap_;
		cv::Mat P_l_,P_r_;//ideal projection matrices
		cv::Rect l_ROI_,r_ROI_;
		Isometry lIso_,lrectIso_;
		Isometry rIso_,rrectIso_;
};

}

#endif