#ifndef SINGLE_CALIBRATOR_HEADER_HPP
#define SINGLE_CALIBRATOR_HEADER_HPP

#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include "DataStructures/CameraInfo/Single.hpp"
#include "Calibration/SingleConfig.hpp"
#include "Calibration/SingleOutput.hpp"

namespace stereo
{
class SingleCalibrator
{
	private:
		void genDirectories();
		std::string full_drawn,full_found,full_not_found;
		std::vector<std::string> tempNames;
		bool genImageList();
		void debugOut(std::string msg,bool newline);
		void getImage(int index,cv::Mat &output);
		std::stringstream msgs_;
		bool getCheckerBoard(cv::Mat input,std::vector<cv::Point2f> &output);
	public:
		SingleConfig configuration_;
		SingleCalibrator(std::string configDir);
		SingleCalibrator(SingleConfig conf);
		bool calibrate(SingleOutput &outputcam);
		
};
	
}

#endif