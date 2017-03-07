#ifndef STEREO_CALIBRATOR_HEADER_HPP
#define STEREO_CALIBRATOR_HEADER_HPP

#include "Calibration/SingleOutput.hpp"
#include "Calibration/StereoOutput.hpp"
#include "Calibration/Calibrator.hpp"


namespace stereo
{

class StereoCalibrator
{
	private:
		void printDebug(std::string msg,bool newline);
		std::stringstream debugMsgs;
		std::vector<std::vector<cv::Point3f> > getVectorBoardCoordinates(int n_images_found);
			void checkCorrespondences(std::vector<cv::Point2f> left,std::vector<cv::Point2f> right,int lindex,int rindex);
	public:
		stereo::StereoConfig config_;
		StereoCalibrator(std::string configDir);
		StereoCalibrator(StereoConfig config);
		bool calibrate(StereoOutput &output);
};
	
}


#endif