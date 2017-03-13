#include "DataStructures/CameraInfo/Stereo.hpp"

namespace stereo
{

Stereo::Stereo()
{

}

Stereo::~Stereo()
{
	
}


void Stereo::read(const cv::FileNode& node)
{
	node["left_camera"]>>cam_left_;
	node["right_camera"]>>cam_right_;
//	node["calibration_size"]>>cal_size_;
	node["essential"]>>essential_;
	node["fundamental"]>>fundamental_;
	node["error"]>>RMS_Error;
}


void Stereo::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"left_camera"<<cam_left_;
	fs<<"right_camera"<<cam_right_;
//	fs<<"calibration_size"<<cal_size_;
	fs<<"essential"<<essential_;
	fs<<"fundamental"<<fundamental_;
	fs<<"error"<<RMS_Error;
	fs<<"}";

}





}