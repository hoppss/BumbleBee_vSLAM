#include "DataStructures/CameraInfo/StereoRect.hpp"

namespace stereo
{

StereoRect::StereoRect(Stereo conf)
{
		conf.QMap_.copyTo(Qmap_);
		conf.cam_left_.rect_mapx_dist_.copyTo(L_fMapx_);
		conf.cam_left_.rect_mapy_dist_.copyTo(L_fMapy_);
		conf.cam_left_.idealP_.copyTo(P_l_);
		l_ROI_=conf.cam_left_.ROI_wD_;
		lIso_=conf.cam_left_.iso_;
		lrectIso_=conf.cam_left_.rectIso_;
		
		conf.cam_right_.rect_mapx_dist_.copyTo(R_fMapx_);
		conf.cam_right_.rect_mapy_dist_.copyTo(R_fMapy_);
		conf.cam_right_.idealP_.copyTo(P_r_);
		r_ROI_=conf.cam_right_.ROI_wD_;
		rIso_=conf.cam_right_.iso_;
		rrectIso_=conf.cam_right_.rectIso_;
}


	
}