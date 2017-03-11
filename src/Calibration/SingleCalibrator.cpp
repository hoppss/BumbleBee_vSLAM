#include "Calibration/SingleCalibrator.hpp"
namespace stereo{
	
SingleCalibrator::SingleCalibrator(std::string configDir)
{
	cv::FileStorage in(configDir,cv::FileStorage::READ);
	in["SingleConfig"]>>configuration_;	
}


SingleCalibrator::SingleCalibrator(SingleConfig conf)
{
	configuration_=conf;
}

void SingleCalibrator::genDirectories()
{
	/*creates the directories in which the output will be saved
	 * by using the system terminal commands*/
	
	std::stringstream comm; //holds the command to be sent to the command line
	std::stringstream fulldir;//holds the "output" directory 
	std::string str_command;//a converted command line, system() only accepts char arrays as input, std::string eases the conversion process
	
	msgs_.str("");
	msgs_<<"Directories created\t";
	
	if(configuration_.saveFound)//create a directory for the found images to be saved
	{
		fulldir.str("");
		fulldir<<configuration_.out_directory<<"/Found";
		comm.str("");
		comm<<"mkdir -pv "<<fulldir.str(); //make directory and all the sub folders
		str_command=comm.str();
		system(str_command.c_str());
		full_found=fulldir.str();
		msgs_<<fulldir.str()<<"\t";
	}
	if(configuration_.saveNotFound) //create a directory for images where no checkerboard is foudn
	{
		fulldir.str("");
		fulldir<<configuration_.out_directory<<"/NotFound";
		comm.str("");
		comm<<"mkdir -pv "<<fulldir.str();
		str_command=comm.str();
		system(str_command.c_str());
		full_not_found=fulldir.str();
		msgs_<<fulldir.str()<<"\t";
	}
	
	
	if(configuration_.saveDrawn) //directory for images where drawn checkerboards are filled in 
	{
		fulldir.str("");
		fulldir<<configuration_.out_directory<<"/Drawn";
		comm.str("");
		comm<<"mkdir -pv "<<fulldir.str();
		str_command=comm.str();
		system(str_command.c_str());
		full_drawn=fulldir.str();
		msgs_<<fulldir.str()<<"\t";
	}
	//output
	fulldir.str("");
	fulldir<<configuration_.out_directory;
	comm.str("");
	comm<<"mkdir -pv "<<fulldir.str();
	str_command=comm.str();
	system(str_command.c_str());
  msgs_<<fulldir.str();
	debugOut(msgs_.str(),true);

}


bool SingleCalibrator::calibrate(SingleOutput &outputcam) 
{
	/* A function that returns true if calibration was succesfull and false otherwise, 
	 * places the output of the calibration in the outputcam variable provided*/
	//clear all the existing information found in the output structure
	outputcam.foundCorners.clear();
	outputcam.fullDirNames.clear();
	outputcam.indivNames.clear();
	outputcam.remapped_corners.clear();
	cv::Size cal_size; //image size
	tempNames.clear();//holds all the input image directory names
	bool Success; //holds return value
	
	Success=genImageList();//generate the set of image directories
	if(Success)
	{
		genDirectories();//create the directory structure
		std::cout<<"finding corners\n";
		for(int dirIndex=0;dirIndex<tempNames.size();dirIndex++)
		{
			std::cout<<"["<<dirIndex+1<<"/"<<tempNames.size()<<"]\n";
			cv::Mat currentInput,checkerBoard;
			getImage(dirIndex,currentInput);
			cal_size=currentInput.size(); /*assuming all images are the same size*/
			std::vector<cv::Point2f> currentFoundPoints;
			bool found=getCheckerBoard(currentInput,currentFoundPoints);
			msgs_.str("");
			msgs_<<"found checkerboard = "<<found<<"\t Image:\t"<<tempNames.at(dirIndex);
			debugOut(msgs_.str(),true);
			
			/*draws the found checkerboard pattern onto the image*/
			cv::cvtColor(currentInput,checkerBoard,cv::COLOR_GRAY2BGR);
			cv::drawChessboardCorners(checkerBoard,configuration_.getBoard(),currentFoundPoints,found);
			bool wait=false;
			
			
			//display and save images
			if(configuration_.displayFound||configuration_.displayNotFound)
			{
				wait=true;
				
			}
				
			if(found)
			{
			
				
				if(configuration_.displayFound)
				{
					cv::namedWindow("checkerboard",CV_WINDOW_NORMAL);
					cv::imshow("checkerboard",checkerBoard);
				}
				if(configuration_.saveDrawn)
				{
					//save the drawn checkerboard pattern image
					std::string dirname=full_drawn;
					dirname+="/";
					dirname+=tempNames.at(dirIndex);
					cv::imwrite(dirname,checkerBoard);
				}
				if(configuration_.saveFound)
				{
					//save all images that had no checkerboard found
					std::string dirname=full_found;
					dirname+="/";
					dirname+=tempNames.at(dirIndex);
					cv::imwrite(dirname,currentInput);
				}
				/* copy found corners and all the image information to the outputcam */
				outputcam.indivNames.push_back(tempNames.at(dirIndex)); 
				outputcam.calibration_size=cal_size;
				std::stringstream fFile;
				fFile<<configuration_.in_directory<<"/"<<tempNames.at(dirIndex);
				outputcam.fullDirNames.push_back(fFile.str());
				outputcam.foundCorners.push_back(currentFoundPoints);			
			}
			else
			{
				if(configuration_.displayNotFound)
				{
					cv::namedWindow("NotFound",CV_WINDOW_NORMAL);
					cv::imshow("NotFound",currentInput);
				}
				if(configuration_.saveNotFound)
				{
					std::string dirname=full_not_found;
					dirname+="/";
					dirname+=tempNames.at(dirIndex);
					cv::imwrite(dirname,currentInput);
				}
				
			}
			if(wait)
			{
				//if any display option are given
				cv::waitKey(0);
				cv::destroyAllWindows();
			}
			
			
		}
		
		//calibrate camera
		
		std::vector<cv::Mat> tempR,tempT;//dummy variables
		cv::Mat tempk,tempd;
		std::cout<<"Calibrating Camera\n";
		if(configuration_.compute_rational_model)
		{
			outputcam.rms_meas=cv::calibrateCamera(configuration_.genSetBoardCoordinate(outputcam.foundCorners.size()),
																				outputcam.foundCorners,
																				cal_size,
																				outputcam.measured_k,outputcam.measured_d,tempR,tempT,CV_CALIB_RATIONAL_MODEL);
		}
		else
		{
			outputcam.rms_meas=cv::calibrateCamera(configuration_.genSetBoardCoordinate(outputcam.foundCorners.size()),
																				outputcam.foundCorners,
																				cal_size,
																				outputcam.measured_k,outputcam.measured_d,tempR,tempT);
		}
		/*Perform undistort and remapping calculations*/
		
		
		cv::Mat r_ident=cv::Mat::eye(3,3,CV_32FC1);
		cv::initUndistortRectifyMap(outputcam.measured_k,outputcam.measured_d,
																r_ident,
															  outputcam.measured_k,outputcam.calibration_size,
															  CV_32FC1,outputcam.undist_mapping_x,outputcam.undist_mapping_y);
		
		cv::Mat original_img,undistorted_img;
		
		for(int index=0;index<outputcam.fullDirNames.size();index++)
			{
				getImage(index,original_img);
				undistorted_img=cv::Mat(original_img.size(),original_img.type());
				cv::remap(original_img,undistorted_img,
								outputcam.undist_mapping_x,outputcam.undist_mapping_y,
								CV_INTER_LINEAR);	
				std::vector<cv::Point2f> newPoints;
				

				bool newFound=false;
				if(getCheckerBoard(undistorted_img,newPoints))
				{
					outputcam.undistortDirNames.push_back(outputcam.fullDirNames.at(index));
					outputcam.remapped_corners.push_back(newPoints);
					newFound=true;
				}
				else
				{
					std::cout<<"rectified checkerboard not found\n";
				}
				
				if(configuration_.displayUndistorted)
				{
					cv::namedWindow("original",CV_WINDOW_NORMAL);
					cv::namedWindow("undistorted",CV_WINDOW_NORMAL);
					
					if((configuration_.displayMapping)&&(newFound))
					{
							cv::cvtColor(undistorted_img,undistorted_img,cv::COLOR_GRAY2BGR);
							cv::drawChessboardCorners(undistorted_img,configuration_.getBoard(),newPoints,newFound);
					}
				
					cv::imshow("undistorted",undistorted_img);
					cv::imshow("original",original_img);
					cv::waitKey(0);
				}

		}
		
		cv::destroyAllWindows();
		
		
		msgs_.str("");
		msgs_<<"calibration Error : "<<outputcam.rms_meas<<std::endl;
		debugOut(msgs_.str(),false);
		//save info 
		outputcam.calibration_size=cal_size;
		outputcam.conf_=configuration_;
		
		std::string outfile;
		outfile=configuration_.out_directory;
		outfile+="/";
		outfile+=configuration_.filename;
		outfile+=".xml";
		
		cv::FileStorage fs(outfile,cv::FileStorage::WRITE);
		fs<<"SingleOutput"<<outputcam;
		fs.release();
		Success=true;
	}
	
	return Success;

}

void SingleCalibrator::undistortPoint(cv::Point2f in, cv::Point2f& out,SingleOutput calib)
{
	float r2=in.x*in.x+in.y*in.y;
	float numerator,denominator,combined;
	numerator=1+calib.measured_d.at<float>(0,0)*r2+calib.measured_d.at<float>(0,1)*r2*r2+calib.measured_d.at<float>(0,4)*r2*r2*r2;
	denominator=1+calib.measured_d.at<float>(0,5)*r2+calib.measured_d.at<float>(0,6)*r2*r2+calib.measured_d.at<float>(0,7)*r2*r2*r2;
	combined=numerator/denominator;
	/*new x position*/
	float x2 =in.x*combined+2*calib.measured_d.at<float>(0,2)*in.x*in.y+calib.measured_d.at<float>(0,3)*(r2+2*in.x*in.x);
	
//	float xNew=(in.x)*()/()
	
}


bool SingleCalibrator::getCheckerBoard(cv::Mat input, std::vector< cv::Point2f >& output)
{
	/*find and store the checkerboard points*/
	bool found=cv::findChessboardCorners(input,
																	configuration_.getBoard(),output,
																  configuration_.getCalibrationFlags());
	if((!found)&&(configuration_.robustCheckerBoard))
	{
		found=robustCheckerBoard(input,output);
	}
	
	return found;
}

bool SingleCalibrator::robustCheckerBoard(cv::Mat input, std::vector< cv::Point2f >& output)
{
	bool found=false;
	int index=0;
	while((!found)&&(index<genAllPossibleChess().size()))
	{
		output.clear();
		found=cv::findChessboardCorners(input,
																	configuration_.getBoard(),output,
																  genAllPossibleChess().at(index));
		index++;
	}
	return found;
}

std::vector< int > SingleCalibrator::genAllPossibleChess()
{
	std::vector<int> Ans;
	Ans.push_back(CV_CALIB_CB_NORMALIZE_IMAGE);
	Ans.push_back(CV_CALIB_CB_FILTER_QUADS);
	Ans.push_back(CV_CALIB_CB_ADAPTIVE_THRESH);	
	Ans.push_back(CV_CALIB_CB_NORMALIZE_IMAGE|CV_CALIB_CB_FILTER_QUADS);
	Ans.push_back(CV_CALIB_CB_NORMALIZE_IMAGE|CV_CALIB_CB_ADAPTIVE_THRESH);
	Ans.push_back(CV_CALIB_CB_FILTER_QUADS|CV_CALIB_CB_ADAPTIVE_THRESH);
	Ans.push_back(CV_CALIB_CB_NORMALIZE_IMAGE|CV_CALIB_CB_FILTER_QUADS|CV_CALIB_CB_ADAPTIVE_THRESH);

	return Ans;
}



bool SingleCalibrator::genImageList()
{
	/*
	 * reads all the file names provided by the input arguments*/
	bool Success=false;
	DIR *dp;
	struct dirent *dirp;
	if((dp=opendir(configuration_.in_directory.c_str())) == NULL)//if unable to open
	{
		std::cerr << "Error(" << errno << ") opening " <<configuration_.in_directory<< std::endl;
		Success=false;
	}
	else
	{
		debugOut("Reading from MainDir",true);
		while( (dirp=readdir(dp))!= NULL) //while there are still files to be read
			{
				std::string readname(dirp->d_name); //read a single file
				bool reject=false; //reject the file
				if((readname.compare("..")==0)||(readname.compare(".")==0))
				{
					/*removes the directories inherent to linux of "." and ".."*/
					reject=true;
				}
			
				if(!reject)//gets rid of the .  and .. directories
				{
					tempNames.push_back(readname);
				}

			}
		closedir(dp);
		std::sort(tempNames.begin(),tempNames.end());//sort in alphabetical i.e first to last taken
		Success=true;
	}
	return Success;
}



void SingleCalibrator::debugOut(std::string msg, bool newline)
{
	/*prints debug information if setup for debugInfo in coniguration file*/
	if(configuration_.debugInfo)
	{
		if(newline)
		{
			std::cout<<"debug: "<<msg<<std::endl;
		}
		else
		{
			std::cout<<"debug: "<<msg;
		}
	}
}

void SingleCalibrator::getImage(int index, cv::Mat& output)
{
	/* gets an image in cv::Mat structure at the specified index */
	std::stringstream inputFile;
	inputFile<<configuration_.in_directory<<"/"<<tempNames.at(index);
	output=cv::imread(inputFile.str(),cv::IMREAD_GRAYSCALE);
	msgs_.str("");
	msgs_<<"Loaded Image "<<inputFile.str();
	debugOut(msgs_.str(),true);
}








	
}