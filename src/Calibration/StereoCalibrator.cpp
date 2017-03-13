#include "Calibration/StereoCalibrator.hpp"

namespace stereo
{
	
StereoCalibrator::StereoCalibrator(std::string configDir)
{
	cv::FileStorage fs;
	fs.open(configDir,cv::FileStorage::READ);
	if(fs.isOpened())
	{
		fs["stereoConfig"]>>config_;
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
	std::vector< std::vector<cv::Point2f> > leftFoundPoints,rightFoundPoints;
	std::vector<std::string> leftImgDir,rightImgDir;
	
	if(config_.compute_left_)
	{
		//calibrate the left camera according
		//to left config file
		//TODO add error codes
	}
	else
	{
	 config_.output_left_.measured_k.copyTo(output.cam_left_.K_meas_);
	 config_.output_left_.measured_d.copyTo(output.cam_left_.dist_);
	 config_.output_left_.undist_mapping_x.copyTo(output.cam_left_.undistort_mapx_);
	 config_.output_left_.undist_mapping_y.copyTo(output.cam_left_.undistort_mapy_);
	 output.cam_left_.originalImg_=config_.output_left_.calibration_size;
	 output.cam_left_.optimized_=false;
	 output.cam_left_.rectified_Wdist=false;
	 leftFoundPoints=config_.output_left_.foundCorners;
	 leftImgDir=config_.output_left_.fullDirNames;
	}

	if(config_.compute_right_)
	{
		//calibrate
		//TODO add error codes
	}
	else
	{
		config_.output_right_.measured_k.copyTo(output.cam_right_.K_meas_);
		config_.output_right_.measured_d.copyTo(output.cam_right_.dist_);
		config_.output_right_.undist_mapping_x.copyTo(output.cam_right_.undistort_mapx_);
		config_.output_right_.undist_mapping_y.copyTo(output.cam_right_.undistort_mapy_);
		output.cam_right_.originalImg_=config_.output_right_.calibration_size;
		output.cam_right_.optimized_=false;
		output.cam_right_.rectified_Wdist=false;
		rightFoundPoints=config_.output_right_.foundCorners;
		rightImgDir=config_.output_right_.fullDirNames;
	}
	
	getOverlap(leftFoundPoints,rightFoundPoints,leftImgDir,rightImgDir);
	
	//dont check for errors, just use the singleOutputs available in the class

	if(config_.showIndividualMatches_)
		{
			cv::namedWindow("correspondences",cv::WINDOW_NORMAL);
			
			std::vector< std::vector<cv::Point2f> >::iterator my_iter,end_iter;
			end_iter=leftFoundPoints.end();
			
			int temp=0;
			std::cout<<"push spacebar to delete image from configuration"<<std::endl;
			while(!(temp>=leftFoundPoints.size()))
			{
				checkCorrespondences(leftFoundPoints.at(temp),rightFoundPoints.at(temp),leftImgDir.at(temp),rightImgDir.at(temp));
				int Delete=cv::waitKey(0);
				std::cout<<Delete<<std::endl;
				if(Delete==32) //if spacebar pushed, remove it
				{
					std::cout<<"removing Incorrect Correspondences at index "<<temp<<std::endl;
					leftFoundPoints.erase(leftFoundPoints.begin()+temp);
					rightFoundPoints.erase(rightFoundPoints.begin()+temp);
					leftImgDir.erase(leftImgDir.begin()+temp);
					rightImgDir.erase(rightImgDir.begin()+temp);
				}
				else
				{
					temp++;
				}
			}
			cv::destroyWindow("correspondences");
		}
		
		cv::Mat tempR,tempT,tempE,tempF;
		if(config_.calib_guess_intrinsic_)
		{
			output.cam_left_.optimized_=true;
			output.cam_right_.optimized_=true;
			config_.output_left_.measured_k.copyTo(output.cam_left_.K_optim_);
			config_.output_left_.measured_d.copyTo(output.cam_left_.dist_optim_);
			config_.output_right_.measured_k.copyTo(output.cam_right_.K_optim_);
			config_.output_right_.measured_d.copyTo(output.cam_right_.dist_optim_);
			
			
			output.RMS_Error=cv::stereoCalibrate(getVectorBoardCoordinates(leftFoundPoints.size()),
												leftFoundPoints,rightFoundPoints,
												output.cam_left_.K_optim_,output.cam_left_.dist_optim_,
												output.cam_right_.K_optim_,output.cam_right_.dist_optim_,
												output.cam_left_.originalImg_,
												tempR,tempT,output.essential_,output.fundamental_,
												cv::TermCriteria(config_.getTerminationFlags(),config_.termination_error_,config_.max_count_),
												config_.getCalibrationFlags());
			
			cv::Mat rot=cv::Mat::eye(3,3,CV_64FC1);
			/*compute new undistort maps*/
			cv::initUndistortRectifyMap(output.cam_left_.K_optim_,output.cam_left_.dist_optim_,rot,
																	output.cam_left_.K_optim_,output.cam_left_.originalImg_,CV_32FC1,
																	output.cam_left_.undistort_mapx_optim_,output.cam_left_.undistort_mapy_optim_);
			
			cv::initUndistortRectifyMap(output.cam_right_.K_optim_,output.cam_right_.dist_optim_,rot,
																	output.cam_right_.K_optim_,output.cam_right_.originalImg_,CV_32FC1,
																	output.cam_right_.undistort_mapx_optim_,output.cam_right_.undistort_mapy_optim_);
			
			/**get stereo settings */
			if(config_.compute_rectify_wDist_)
			{
				output.cam_left_.rectified_Wdist=true;
				output.cam_right_.rectified_Wdist=true;
							cv::stereoRectify(output.cam_left_.K_optim_,output.cam_left_.dist_optim_,
												output.cam_right_.K_optim_,output.cam_right_.dist_optim_,
												output.cam_left_.originalImg_,tempR,tempT,
												output.cam_left_.RectR,output.cam_right_.RectR,
												output.cam_left_.idealP_,output.cam_right_.idealP_,output.QMap_,
												0,1,output.Rectsize_,
												&output.cam_left_.ROI_wD_,&output.cam_right_.ROI_wD_);	
							
							cv::initUndistortRectifyMap(output.cam_left_.K_optim_,output.cam_left_.dist_optim_,output.cam_left_.RectR,
																					output.cam_left_.idealP_,output.cam_left_.ROI_wD_.size(),CV_32FC1,
																					output.cam_left_.rect_mapx_dist_,output.cam_left_.rect_mapy_dist_);
							
							cv::initUndistortRectifyMap(output.cam_right_.K_optim_,output.cam_right_.dist_optim_,output.cam_right_.RectR,
																					output.cam_right_.idealP_,output.cam_left_.ROI_wD_.size(),CV_32FC1,
																					output.cam_right_.rect_mapx_dist_,output.cam_right_.rect_mapy_dist_);
							
			}
			cv::stereoRectify(output.cam_left_.K_optim_,cv::Mat::zeros(5,1,CV_64FC1),
												output.cam_right_.K_optim_,cv::Mat::zeros(5,1,CV_64FC1),
												output.cam_left_.originalImg_,tempR,tempT,
												output.cam_left_.RectR,output.cam_right_.RectR,
												output.cam_left_.idealP_,output.cam_right_.idealP_,output.QMap_,
												0,1,output.Rectsize_,
												&output.cam_left_.ROI_,&output.cam_right_.ROI_);	
			
			
			
			cv::initUndistortRectifyMap(output.cam_left_.K_optim_,cv::Mat::zeros(5,1,CV_64FC1),output.cam_left_.RectR,
																	output.cam_left_.idealP_,output.cam_left_.ROI_.size(),CV_32FC1,
																	output.cam_left_.rect_mapx_,output.cam_left_.rect_mapy_);
			
			cv::initUndistortRectifyMap(output.cam_right_.K_optim_,cv::Mat::zeros(5,1,CV_64FC1),output.cam_right_.RectR,
																	output.cam_right_.idealP_,output.cam_right_.ROI_.size(),CV_32FC1,
																	output.cam_right_.rect_mapx_,output.cam_right_.rect_mapy_);
			
			/*compute Isometries*/
			Isometry left,leftRect;
			Isometry right,rightRect;
			//left Origin
			left.setIdentity();
			leftRect.setRT(output.cam_left_.RectR,cv::Mat::zeros(3,1,CV_64FC1));

			//		
			right.setRT(tempR,tempT);
			rightRect.setRT(output.cam_right_.RectR,cv::Mat::zeros(3,1,CV_64FC1));
			
			output.cam_left_.rectIso_=leftRect;
			output.cam_left_.iso_=left;
			
			output.cam_right_.rectIso_=rightRect;
			output.cam_right_.iso_=right;
			/* compute essential and fundamental*/			

		}
		
		else
		{
				output.RMS_Error=cv::stereoCalibrate(getVectorBoardCoordinates(leftFoundPoints.size()),
												leftFoundPoints,rightFoundPoints,
												output.cam_left_.K_meas_,output.cam_left_.dist_,
												output.cam_right_.K_meas_,output.cam_right_.dist_,
												output.cam_left_.originalImg_,
												tempR,tempT,output.essential_,output.fundamental_,
												cv::TermCriteria(config_.getTerminationFlags(),config_.termination_error_,config_.max_count_),
												config_.getCalibrationFlags());
				
				/*using already computed distortion maps because we are not optimzing the intrinsics at all*/
				/**get stereo settings */
				
					/**get stereo settings */
			if(config_.compute_rectify_wDist_)
			{
				output.cam_left_.rectified_Wdist=true;
				output.cam_right_.rectified_Wdist=true;
							cv::stereoRectify(output.cam_left_.K_meas_,output.cam_left_.dist_,
												output.cam_right_.K_meas_,output.cam_right_.dist_,
												output.cam_left_.originalImg_,tempR,tempT,
												output.cam_left_.RectR,output.cam_right_.RectR,
												output.cam_left_.idealP_,output.cam_right_.idealP_,output.QMap_,
												0,1,output.Rectsize_,
												&output.cam_left_.ROI_wD_,&output.cam_right_.ROI_wD_);	
							
							cv::initUndistortRectifyMap(output.cam_left_.K_meas_,output.cam_left_.dist_,output.cam_left_.RectR,
																					output.cam_left_.idealP_,output.cam_left_.ROI_wD_.size(),CV_32FC1,
																					output.cam_left_.rect_mapx_dist_,output.cam_left_.rect_mapy_dist_);
							
							cv::initUndistortRectifyMap(output.cam_right_.K_meas_,output.cam_right_.dist_,output.cam_right_.RectR,
																					output.cam_right_.idealP_,output.cam_left_.ROI_wD_.size(),CV_32FC1,
																					output.cam_right_.rect_mapx_dist_,output.cam_right_.rect_mapy_dist_);
							
			}
			cv::stereoRectify(output.cam_left_.K_meas_,cv::Mat::zeros(5,1,CV_64FC1),
												output.cam_right_.K_meas_,cv::Mat::zeros(5,1,CV_64FC1),
												output.cam_left_.originalImg_,tempR,tempT,
												output.cam_left_.RectR,output.cam_right_.RectR,
												output.cam_left_.idealP_,output.cam_right_.idealP_,output.QMap_,
												0,1,output.Rectsize_,
												&output.cam_left_.ROI_,&output.cam_right_.ROI_);	
			
			
			
			cv::initUndistortRectifyMap(output.cam_left_.K_meas_,cv::Mat::zeros(5,1,CV_64FC1),output.cam_left_.RectR,
																	output.cam_left_.idealP_,output.cam_left_.ROI_.size(),CV_32FC1,
																	output.cam_left_.rect_mapx_,output.cam_left_.rect_mapy_);
			
			cv::initUndistortRectifyMap(output.cam_right_.K_meas_,cv::Mat::zeros(5,1,CV_64FC1),output.cam_right_.RectR,
																	output.cam_right_.idealP_,output.cam_right_.ROI_.size(),CV_32FC1,
																	output.cam_right_.rect_mapx_,output.cam_right_.rect_mapy_);
				/*computeIsometries*/
			Isometry left,leftRect;
			Isometry right,rightRect;
			//left Origin
			left.setIdentity();
			leftRect.setRT(output.cam_left_.RectR,cv::Mat::zeros(3,1,CV_64FC1));

			//		
			right.setRT(tempR,tempT);
			rightRect.setRT(output.cam_right_.RectR,cv::Mat::zeros(3,1,CV_64FC1));
			
			output.cam_left_.rectIso_=leftRect;
			output.cam_left_.iso_=left;
			
			output.cam_right_.rectIso_=rightRect;
			output.cam_right_.iso_=right;
			/* compute essential and fundamental*/
				
		}
		Success=true;

		
		std::cout<<"-----\nCalibration Successfull\nstereo error : "<<output.RMS_Error<<"\n----\n";
		printDebug("Creating Directories",true);
		//create the output directory
		std::stringstream command;
		std::string char_command;
		command.str("");
		command<<"mkdir -pv "<<config_.outputDirectory;
		char_command=command.str();
		system(char_command.c_str());
		
		std::string namefile;
		namefile=config_.outputDirectory;
		namefile+="/";
		namefile+=config_.StereoName;
		
		cv::FileStorage fs(namefile,cv::FileStorage::WRITE);
		fs<<"stereocalibration"<<output;
		fs.release();
		std::cout<<"configuration saved to "<<namefile<<std::endl;

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

void StereoCalibrator::checkCorrespondences(std::vector< cv::Point2f > left, std::vector< cv::Point2f > right,std::string lDir,std::string rDir)
{
	//create image
	cv::Mat outputImage;
	cv::Mat leftImage,rightImage;
	
		
	
	leftImage=cv::imread(lDir,cv::IMREAD_GRAYSCALE);
	rightImage=cv::imread(rDir,cv::IMREAD_GRAYSCALE);
	
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


void StereoCalibrator::getOverlap(std::vector< std::vector< cv::Point2f > >& leftPoints, std::vector< std::vector< cv::Point2f > >& rightPoints, std::vector< std::string > &leftImages, std::vector< std::string > &rightImages)
{
	/**
	 * we can only use images in which the checkerboard pattern was found in both the left and right images...
	 * Thus the set of found images for each seperate camera must be compared against one another
	 * and only the where both are present, is the vector of points compared and added for the calibration*/
	std::vector< std::vector< cv::Point2f > > tempLPoints,tempRPoints;
	std::vector<std::string> fullL,fullR;
	
	std::vector< std::string > stripped_leftNames,stripped_rightNames;
	stripped_leftNames=stripPrefixes(leftImages);
	stripped_rightNames=stripPrefixes(rightImages);
	
	for(int index=0;index<stripped_leftNames.size();index++)
	{
		std::vector<std::string>::iterator foundIt=std::find(stripped_rightNames.begin(),stripped_rightNames.end(),stripped_leftNames.at(index));
		int rDistance=std::distance(stripped_rightNames.begin(),foundIt);
		if(foundIt!=stripped_rightNames.end())
		{
			tempLPoints.push_back(leftPoints.at(index));
			fullL.push_back(leftImages.at(index));
			
			tempRPoints.push_back(rightPoints.at(rDistance));
			fullR.push_back(rightImages.at(rDistance));			
		}
	}
	
	leftPoints=tempLPoints;
	rightPoints=tempRPoints;
	leftImages=fullL;
	rightImages=fullR;

}

std::vector< std::string > StereoCalibrator::stripPrefixes(std::vector< std::string > in)
{
	/* removes all the prefixes in front of the image names up to the last underscore
	 * Note:: DataSet must adhere to these naming conventions */
	std::vector< std::string > Ans;
	for(int index=0;index<in.size();index++)
	{
		size_t found=in.at(index).find_last_of("_");
		std::string shortened=in.at(index);
		shortened.erase(shortened.begin(),shortened.begin()+found);
		Ans.push_back(shortened);
	}
	return Ans;
}




	
	
}