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
		bool stereo_rectified_withDistort_;//calculated relative to the original image
		Single cam_left_,cam_right_;	
		cv::Mat essential_,rect_essential_;
		cv::Mat fundamental_,rect_fundamental_;
		cv::Mat QMap_;
		double RMS_Error;
		cv::Size Rectsize_;//calibration

		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
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