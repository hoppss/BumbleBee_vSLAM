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
	/* Single Camera Calibrator 
	 * A class that uses a single camera configuration to calibrate a camera, and save it to the
	 * SingleOutput data structure for further processing */
class SingleCalibrator
{
	private:
		void undistortPoint(cv::Point2f in,cv::Point2f &out,SingleOutput calib);
		void genDirectories();
		std::string full_drawn,full_found,full_not_found;
		std::vector<std::string> tempNames;
		std::vector<int> genAllPossibleChess();//generates all the
		bool genImageList();
		void debugOut(std::string msg,bool newline);
		void getImage(int index,cv::Mat &output);
		std::stringstream msgs_;
		bool getCheckerBoard(cv::Mat input,std::vector<cv::Point2f> &output);
		bool robustCheckerBoard(cv::Mat input,std::vector<cv::Point2f> &output);
	public:
		SingleConfig configuration_;
		SingleCalibrator(std::string configDir);
		SingleCalibrator(SingleConfig conf);
		bool calibrate(SingleOutput &outputcam);
		
};
	
}

#endif