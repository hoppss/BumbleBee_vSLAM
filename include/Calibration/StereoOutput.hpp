#ifndef STEREO_OUTPUT_HEADER_HPP
#define STEREO_OUTPUT_HEADER_HPP

#include "Calibration/SingleOutput.hpp"
#include "DataStructures/CameraInfo/Stereo.hpp"

namespace stereo
{
class StereoOutput
{
	private:
	/*	cv::Mat essential_;
		cv::Mat fundamental_;
		cv::Mat baseline_T_;
		cv::Mat baseline_R_;
		double meas_error;
		std::vector<std::vector<cv::Point3f> >  getChessPoints(cv::Size board,double square_size, int n);
		Stereo generateStereo();*/
	public:
		StereoOutput();
//		bool calibrateStereo(SingleOutput &left,SingleOutput &right);
	//	void saveConfiguration(std::string dir, bool lean,SingleOutput& left, SingleOutput& right);
		//lean saves only the essential camera parameters
		
		
};
	
}

#endif