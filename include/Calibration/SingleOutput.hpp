#ifndef SINGLE_OUTPUT_HEADER_HPP
#define SINGLE_OUTPUT_HEADER_HPP

#include <highgui.h>


#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>


#include <iostream>

#include "DataStructures/CameraInfo/Single.hpp"
#include "Calibration/SingleConfig.hpp"
namespace stereo
{
	
class SingleOutput
{
	public:
		SingleOutput();
		SingleConfig conf_;
		std::vector< std::vector<cv::Point2f> > foundCorners;
		std::vector<std::string> fullDirNames,indivNames;
		Single calibration;
		double rms_meas;
		cv::Mat measured_k;
		cv::Mat measured_d;
		cv::Size calibration_size;
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
		friend class StereoOutput;
	
};

static void read(const cv::FileNode& node, stereo::SingleOutput& x, const stereo::SingleOutput& default_value = stereo::SingleOutput()){
   if(node.empty())
	{
        x = default_value;
	}
    else
	{
        x.read(node);
	}
}

static void write(cv::FileStorage& fs, const std::string&, const stereo::SingleOutput& x)
{
    x.write(fs);
}

}



#endif