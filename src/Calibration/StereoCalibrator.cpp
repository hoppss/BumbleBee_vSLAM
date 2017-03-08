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


bool StereoCalibrator::calibrate(Stereo& output)
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
		//TODO adjust method to include guesses at the internal configuration
		double error;
		cv::Mat tempR,tempT,tempE,tempF;
		error=cv::stereoCalibrate(getVectorBoardCoordinates(leftFoundPoints.size()),
												leftFoundPoints,rightFoundPoints,
												config_.output_left_.measured_k,config_.output_left_.measured_d,
												config_.output_right_.measured_k,config_.output_right_.measured_d,
												config_.output_left_.calibration_size,
												tempR,tempT,tempE,tempF,
												cv::TermCriteria(config_.getTerminationFlags(),config_.termination_error_,config_.max_count_),
												config_.getCalibrationFlags());
		std::cout<<"-----\nCalibration Successfull\nstereo error : "<<error<<"\n----\n";
		std::cout<<"BaseLine:\t"<<tempR<<"\t"<<tempT<<std::endl;
		std::cout<<"EpiPolar Config\tF:"<<tempF<<"\tE:"<<tempE<<std::endl;
		
		cv::Mat pLeft,pRight,Rleft,Rright,Qmap; //rectification parameter outputs
		if(config_.compute_rectify_)
		{
			//TODO rectify and compute mapping 
		}
		
		
		

		Isometry leftCoord,rightCoord;
		
		leftCoord.setIdentity();
		rightCoord.setRT(tempR,tempT);
		rightCoord.invertThis();//inverting because we want coordinate as seen by the left camera, the origin
		
		Single leftCamera(config_.output_left_.measured_k,
											config_.output_left_.measured_d,
											leftCoord);
		leftCamera.RMS_Error=config_.output_left_.rms_meas;
		Single rightCamera(config_.output_right_.measured_k,
											 config_.output_right_.measured_d,
											 rightCoord);
		rightCamera.RMS_Error=config_.output_right_.rms_meas;
		
		output.cam_left_=leftCamera;
		output.cam_right_=rightCamera;
		tempE.copyTo(output.essential_);
		tempF.copyTo(output.fundamental_);
		output.RMS_Error=error;
		printDebug("Creating Directories",true);
		//create the output directory
		std::stringstream command;
		std::string char_command;
		command.str("");
		command<<"mkdir -p "<<config_.outputDirectory;
		char_command=command.str();
		system(char_command.c_str());
		
		std::string namefile;
		namefile=config_.outputDirectory;
		namefile+="/";
		namefile+=config_.StereoName;
		
		cv::FileStorage fs(namefile,cv::FileStorage::WRITE);
		fs<<"stereocalibration"<<output;
		fs.release();
		std::cout<<"configuratoin saved to "<<namefile<<std::endl;
		
		
		
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