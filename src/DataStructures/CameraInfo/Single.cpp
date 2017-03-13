#include "DataStructures/CameraInfo/Single.hpp"

namespace stereo
{
	
Single::Single()
{
		RMS_Error=-1;
		iso_.setIdentity();
		optimized_=false;
		rectified_Wdist=false;
		//NOTE  k and D are not set, error will occur if referenced 
}

Single::Single(cv::Mat k,cv::Mat dist,Isometry is)
{
	RMS_Error=-1;
	setData(k,dist,is);
}


Single::~Single()
{
	//K_.release();
	//K_dist_.release();
}

void Single::setData(cv::Mat k,cv::Mat dist,Isometry is)
{
//	k.copyTo(K_);
//	dist.copyTo(K_dist_);
//	iso_=is;
}


void Single::printInternals()
{
//	std::cout<<"K: "<<K_<<std::endl;
//	std::cout<<"Distortion: "<<K_dist_<<std::endl;
//	std::cout<<"RMS Error : "<<RMS_Error<<std::endl;
//	std::cout<<"World Coordinate System to Camera Coordinate System\n";
//	iso_.printH();

}


	

//input output xml functions

void Single::read(const cv::FileNode& node)
{

//	node["intrinsics"]>>K_;
//	node["distortion"]>>K_dist_;
//	node["isometry"]>>iso_;
//	node["RMS"]>>RMS_Error;

	node["meas_k"]>>K_meas_;
	node["meas_d"]>>dist_;
	node["meas_mapone"]>>undistort_mapx_;
	node["meas_maptwo"]>>undistort_mapy_;
	node["imageSize"]>>originalImg_;
	node["optimized"]>>optimized_;
	node["optim_k"]>>K_optim_;
	node["optim_d"]>>dist_optim_;
	node["optim_mapone"]>>undistort_mapx_optim_;
	node["optim_maptwo"]>>undistort_mapy_optim_;
	node["rect_wDist"]>>rectified_Wdist;
	node["roi_wd"]>>ROI_wD_;
	node["roi"]>>ROI_;
	node["rect_mapone"]>>rect_mapx_;
	node["rect_maptwo"]>>rect_mapy_;
	node["rect_mapone_d"]>>rect_mapx_dist_;
	node["rect_maptwo_d"]>>rect_mapy_dist_;
	node["rectR"]>>RectR;
	node["idealP"]>>idealP_;
	node["isometry"]>>iso_;
	node["isometry_rect"]>>rectIso_;
	node["RMS"]>>RMS_Error;

}

void Single::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"meas_k"<<K_meas_;
	fs<<"meas_d"<<dist_;
	fs<<"meas_mapone"<<undistort_mapx_;
	fs<<"meas_maptwo"<<undistort_mapy_;
	fs<<"imageSize"<<originalImg_;
	fs<<"optimized"<<optimized_;
	fs<<"optim_k"<<K_optim_;
	fs<<"optim_d"<<dist_optim_;
	fs<<"optim_mapone"<<undistort_mapx_optim_;
	fs<<"optim_maptwo"<<undistort_mapy_optim_;
	fs<<"rect_wDist"<<rectified_Wdist;
	fs<<"roi_wd"<<ROI_wD_;
	fs<<"roi"<<ROI_;
	fs<<"rect_mapone"<<rect_mapx_;
	fs<<"rect_maptwo"<<rect_mapy_;
	fs<<"rect_mapone_d"<<rect_mapx_dist_;
	fs<<"rect_maptwo_d"<<rect_mapy_dist_;
	fs<<"rectR"<<RectR;
	fs<<"idealP"<<idealP_;
	fs<<"isometry"<<iso_;
	fs<<"isometry_rect"<<rectIso_;
	fs<<"RMS"<<RMS_Error;
	fs<<"}";


}





}