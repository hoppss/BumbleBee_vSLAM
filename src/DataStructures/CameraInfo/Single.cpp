#include "DataStructures/CameraInfo/Single.hpp"

namespace stereo
{
	
Single::Single()
{
		RMS_Error=-1;
		iso_.setIdentity();
}

Single::Single(cv::Mat k,cv::Mat dist,Isometry is)
{
	RMS_Error=-1;
	setData(k,dist,is);
}


Single::~Single()
{
	K_.release();
	K_dist_.release();
}

void Single::setData(cv::Mat k,cv::Mat dist,Isometry is)
{
	k.copyTo(K_);
	dist.copyTo(K_dist_);
	iso_=is;
}


void Single::printInternals()
{
	std::cout<<"K: "<<K_<<std::endl;
	std::cout<<"Distortion: "<<K_dist_<<std::endl;
	std::cout<<"RMS Error : "<<RMS_Error<<std::endl;
	std::cout<<"World Coordinate System to Camera Coordinate System\n";
	iso_.printH();

}


	

//input output xml functions

void Single::read(const cv::FileNode& node)
{

	node["intrinsics"]>>K_;
	node["distortion"]>>K_dist_;
	node["isometry"]>>iso_;
	node["RMS"]>>RMS_Error;
}

void Single::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"intrinsics"<<K_;
	fs<<"distortion"<<K_dist_;
	fs<<"isometry"<<iso_;
	fs<<"RMS"<<RMS_Error;
	fs<<"}";
}





}