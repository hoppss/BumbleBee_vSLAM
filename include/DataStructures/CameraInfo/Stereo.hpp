#ifndef STEREO__HEADER_HPP
#define STEREO__HEADER_HPP

#include "DataStructures/CameraInfo/Single.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

namespace stereo {

class Stereo
{
	private:
		Single cam_left_,cam_right_;	
		cv::Size cal_size_;//calibration
		Isometry toPixel;
	public:
		Stereo();
		~Stereo();
		//set methods
		void setCameraInfo(bool left,cv::Mat k,cv::Mat dist,Isometry iso);
		void setPixel(Isometry pix);
		void setCalibImgSize(cv::Size calib);
		//structures
		enum CoordinateSystem
		{
			LeftCamera,//the left camera is the origin of the world i.e no transfrom from dataset to pixel coordinates
			LeftPixel//in terms of left pixel coordinates, transform from dataset to the standard computer vision coordinate frame
		};
		//output
		void printConfig(CoordinateSystem sys);
		cv::Mat getEssentialMatrix(CoordinateSystem sys);
		cv::Mat getFundamentalMatrix(CoordinateSystem sys);
		Isometry getBaseline(CoordinateSystem sys);
		double RMS_Error;
		
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
	protected:
		friend class StereoCamera;
};

//These write and read functions must be defined for the serialization in FileStorage to work

static void read(const cv::FileNode& node, stereo::Stereo& x, const stereo::Stereo& default_value = stereo::Stereo()){
    if(node.empty())
	{
        x = default_value;
	}
    else
	{
        x.read(node);
	}
}

static void write(cv::FileStorage& fs, const std::string&, const stereo::Stereo& x)
{
    x.write(fs);
}



}

#endif