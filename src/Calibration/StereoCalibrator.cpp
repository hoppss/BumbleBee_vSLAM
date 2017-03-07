#include "Calibration/StereoCalibrator.hpp"

namespace stereo
{
	
StereoCalibrator::StereoCalibrator(std::string configDir)
{
	cv::FileStorage fs;
	fs.open(configDir,cv::FileStorage::READ);
	if(fs.isOpened())
	{
		fs["stereoconfig"]>>config_;
		fs.release();
	}
	else
	{
		std::cout<<"stereo configuration file not Found\n";
	}
	
}

StereoCalibrator::StereoCalibrator(StereoConfig config)
{
	config_=config;
}


bool StereoCalibrator::calibrate(StereoOutput& output)
{
	bool Success;
	if(config_.compute_left_)
	{
		//calibrate the left camera according
		//to left config file
		//TODO add error codes
	}
	
	if(config_.compute_right_)
	{
		//calibrate
		//TODO add error codes
	}
	
	if((!config_.compute_right_)&&(!config_.compute_left_))
	{
		//dont check for errors, just use the singleOutputs available in the class
		double error;
		cv::Mat tempR,tempT,tempE,tempF;
		cv::stereoCalibrate(config_.output_left_.conf_.genBoardCoordinate(),
												config_.output_left_.foundCorners,config_.output_right_.foundCorners,
												config_.output_left_.measured_k,config_.output_left_.measured_d,
												config_.output_right_.measured_k,config_.output_right_.measured_d,
												config_.output_left_.calibration_size,
												tempR,tempT,tempE,tempF);
	
		
		
	}
	//TODO add functions to perform the calibration if a singleconfig file is give instead of precomputed info
	
	return Success;

}

	
	
}