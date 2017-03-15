#include "FrontEnd/StereoFeatures/StereoRectifiedInternal.hpp"

namespace stereo
{


StereoRectifiedInternal::StereoRectifiedInternal() : StereoInternal()
{

}

StereoRectifiedInternal::~StereoRectifiedInternal()
{
	if(ptr_cal_!=nullptr)
	{
		delete ptr_cal_;
	}
}


bool StereoRectifiedInternal::LoadCameraSettings(std::string dir)
{
	cv::FileStorage fs(dir,cv::FileStorage::READ);
	if(fs.isOpened())
	{
		Stereo myCam;
		fs["stereocalibration"]>>myCam;
		fs.release();
		return LoadCameraSettings(myCam);
	}
	else
	{
		std::cout<<"error: failed to load file"<<std::endl;
		return false;
	}
}

bool StereoRectifiedInternal::LoadCameraSettings(Stereo conf)
{
	if(conf.cam_left_.rectified_Wdist&&conf.cam_right_.rectified_Wdist)
	{
		ptr_cal_=new StereoRect(conf);
		return true;
	}
	else
	{
		std::cout<<"error: inputfile does not have rectification mapping computed"<<std::endl;
		return false;
	}

	return true;
}

	
	
}