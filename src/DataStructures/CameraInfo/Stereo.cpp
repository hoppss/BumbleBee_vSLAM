#include "DataStructures/CameraInfo/Stereo.hpp"

namespace stereo
{

Stereo::Stereo()
{

}

Stereo::~Stereo()
{
	
}

void Stereo::printROI()
{
	std::cout<<"rectSize"<<Rectsize_<<std::endl;
	std::cout<<"---leftCamera"<<std::endl;
	std::cout<<"ROI"<<cam_left_.ROI_.size()<<std::endl;
	std::cout<<"ROIWd"<<cam_left_.ROI_wD_.size()<<std::endl;
	std::cout<<"mapxDist"<<cam_left_.rect_mapx_dist_.size()<<std::endl;
	std::cout<<"mapx"<<cam_left_.rect_mapx_.size()<<std::endl;
	std::cout<<"---rightCamera"<<std::endl;
	std::cout<<"ROI"<<cam_right_.ROI_.size()<<std::endl;
	std::cout<<"ROIWd"<<cam_right_.ROI_wD_.size()<<std::endl;
	std::cout<<"mapxDist"<<cam_right_.rect_mapx_dist_.size()<<std::endl;
	std::cout<<"mapx"<<cam_right_.rect_mapx_.size()<<std::endl;
}



void Stereo::read(const cv::FileNode& node)
{
	node["left_camera"]>>cam_left_;
	node["right_camera"]>>cam_right_;
	node["stereo_withDistort"]>>stereo_rectified_withDistort_;
	node["essential"]>>essential_;
	node["rect_essential"]>>rect_essential_;
	node["rect_fundamental"]>>rect_fundamental_;
	node["rectSize"]>>Rectsize_;
	node["QMap"]>>QMap_;
	node["fundamental"]>>fundamental_;
	node["error"]>>RMS_Error;
	
}


void Stereo::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"left_camera"<<cam_left_;
	fs<<"right_camera"<<cam_right_;
	fs<<"essential"<<essential_;
	fs<<"rect_essential"<<rect_essential_;
	fs<<"rect_fundamental"<<rect_fundamental_;
	fs<<"rectSize"<<Rectsize_;
	fs<<"QMap"<<QMap_;
	fs<<"fundamental"<<fundamental_;
	fs<<"error"<<RMS_Error;
	fs<<"}";

}





}