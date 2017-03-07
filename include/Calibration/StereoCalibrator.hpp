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
	public:
		stereo::StereoConfig config_;
		StereoCalibrator(std::string configDir);
		StereoCalibrator(StereoConfig config);
		bool calibrate(StereoOutput &output);
};
	
}


#endif