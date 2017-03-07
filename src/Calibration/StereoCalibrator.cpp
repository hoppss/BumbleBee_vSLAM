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
	bool Success=false;
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
		std::vector< std::vector<cv::Point2f> > leftFoundPoints,rightFoundPoints;
		std::vector<int> leftIndex,rightIndex;
		config_.getMatchesOverlap(leftFoundPoints,rightFoundPoints,leftIndex,rightIndex);
		
		//dont check for errors, just use the singleOutputs available in the class

		double error;
		cv::Mat tempR,tempT,tempE,tempF;
		error=cv::stereoCalibrate(getVectorBoardCoordinates(leftFoundPoints.size()),
												leftFoundPoints,rightFoundPoints,
												config_.output_left_.measured_k,config_.output_left_.measured_d,
												config_.output_right_.measured_k,config_.output_right_.measured_d,
												config_.output_left_.calibration_size,
												tempR,tempT,tempE,tempF);
		std::cout<<"-----\nstereo error : "<<error<<"\n----\n";

		Success=true;
	}
	//TODO add functions to perform the calibration if a singleconfig file is give instead of precomputed info
	
	return Success;

}

std::vector< std::vector< cv::Point3f > > StereoCalibrator::getVectorBoardCoordinates(int n_images_found)
{
	std::vector< std::vector< cv::Point3f > > Ans;
	for(int index=0;index<n_images_found;index++)
	{
		Ans.push_back(config_.output_left_.conf_.genBoardCoordinate());
	}
	return Ans;
}


void StereoCalibrator::printDebug(std::string msg,bool newline)
{
	if(config_.debugInfo_)
	{
		std::cout<<msg;
		if(newline)
		{
			std::cout<<std::endl;
		}
	}
}


	
	
}