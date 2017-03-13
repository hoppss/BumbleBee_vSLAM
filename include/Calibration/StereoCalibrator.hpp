#ifndef STEREO_CALIBRATOR_HEADER_HPP
#define STEREO_CALIBRATOR_HEADER_HPP

#include "Calibration/SingleOutput.hpp"
#include "Calibration/StereoConfig.hpp"
#include "DataStructures/CameraInfo/Stereo.hpp"




namespace stereo
{

class StereoCalibrator
{
	private:
		void printDebug(std::string msg,bool newline);
		std::stringstream debugMsgs;
		std::vector<std::vector<cv::Point3f> > getVectorBoardCoordinates(int n_images_found);
		void getOverlap(std::vector< std::vector<cv::Point2f> > &leftPoints,
										std::vector< std::vector<cv::Point2f> > &rightPoints,
										std::vector<std::string> &leftImages,
										std::vector<std::string> &rightImages);
		std::vector<std::string> stripPrefixes(std::vector<std::string> in);
		void checkCorrespondences(std::vector<cv::Point2f> left,std::vector<cv::Point2f> right,std::string lDir,std::string rDir);
	public:
		stereo::StereoConfig config_;
		StereoCalibrator(std::string configDir);
		StereoCalibrator(StereoConfig config);
		bool calibrate(Stereo &output);
};
	
}


#endif