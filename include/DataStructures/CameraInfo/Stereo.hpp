#ifndef STEREO__HEADER_HPP
#define STEREO__HEADER_HPP

#include "DataStructures/CameraInfo/Single.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

namespace stereo {

class Stereo
{
	public:
		Stereo();
		~Stereo();
		bool stereo_rectified_withDistort_;//calculated relative to the original image //REDUNDANT TODO
		Single cam_left_,cam_right_;	
		cv::Mat essential_,rect_essential_; //TODO REDUNDANT
		cv::Mat fundamental_,rect_fundamental_;
		cv::Mat QMap_;
		double RMS_Error;
		cv::Size Rectsize_;//TODO redundant
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
		void printROI();
	protected:

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