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
		if(config_.showIndividualMatches_)
		{
			cv::namedWindow("correspondences",cv::WINDOW_NORMAL);
			for(int temp=0;temp<leftFoundPoints.size();temp++)
			{
				checkCorrespondences(leftFoundPoints.at(temp),rightFoundPoints.at(temp),leftIndex.at(temp),rightIndex.at(temp));
				cv::waitKey(0);
			}
			cv::destroyWindow("correspondences");
		}

		double error;
		cv::Mat tempR,tempT,tempE,tempF;
		error=cv::stereoCalibrate(getVectorBoardCoordinates(leftFoundPoints.size()),
												leftFoundPoints,rightFoundPoints,
												config_.output_left_.measured_k,config_.output_left_.measured_d,
												config_.output_right_.measured_k,config_.output_right_.measured_d,
												config_.output_left_.calibration_size,
												tempR,tempT,tempE,tempF);
		std::cout<<"-----\nCalibration Successfull\nstereo error : "<<error<<"\n----\n";
		std::cout<<"BaseLine:\t"<<tempR<<"\t"<<tempT<<std::endl;
		std::cout<<"EpiPolar Config\tF:"<<tempF<<"\tE:"<<tempE<<std::endl;
		
		
		Success=true;
	}
	//TODO add functions to perform the calibration if a singleconfig file is
//	give instead of precomputed info
	
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

void StereoCalibrator::checkCorrespondences(std::vector< cv::Point2f > left, std::vector< cv::Point2f > right, int lindex, int rindex)
{
	//create image
	cv::Mat outputImage;
	cv::Mat leftImage,rightImage;
	
		
	
	leftImage=cv::imread(config_.output_left_.fullDirNames.at(lindex),cv::IMREAD_GRAYSCALE);
	rightImage=cv::imread(config_.output_right_.fullDirNames.at(rindex),cv::IMREAD_GRAYSCALE);
	
	outputImage=cv::Mat(leftImage.size().height,leftImage.size().width+rightImage.size().width,leftImage.type());
	
	leftImage.copyTo(outputImage(cv::Rect(0,0,leftImage.size().width,leftImage.size().height)));
	rightImage.copyTo(outputImage(cv::Rect(leftImage.size().width,0,rightImage.size().width,rightImage.size().height)));

	cv::cvtColor(outputImage,outputImage,cv::COLOR_GRAY2BGR);
	
	for(int index=0;index<left.size();index++)
	{
		cv::Point2f offset=right.at(index);
		offset.x+=leftImage.size().width;
		cv::line(outputImage,left.at(index),offset,cv::Scalar(0,255,0));
	}
	cv::imshow("correspondences",outputImage);

	
	
}



	
	
}