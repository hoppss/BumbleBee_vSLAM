#include "Calibration/SingleCalibrator.hpp"
namespace stereo{
	
SingleCalibrator::SingleCalibrator(std::string configDir)
{
	cv::FileStorage in(configDir,cv::FileStorage::READ);
	in["configuration"]>>configuration_;	
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
		comm<<"mkdir -p "<<fulldir.str(); //make directory and all the sub folders
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
		comm<<"mkdir -p "<<fulldir.str();
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
		comm<<"mkdir -p "<<fulldir.str();
		str_command=comm.str();
		system(str_command.c_str());
		full_drawn=fulldir.str();
		msgs_<<fulldir.str()<<"\t";
	}
	//output
	fulldir.str("");
	fulldir<<configuration_.out_directory;
	comm.str("");
	comm<<"mkdir -p "<<fulldir.str();
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
		outputcam.rms_meas=cv::calibrateCamera(configuration_.genSetBoardCoordinate(outputcam.foundCorners.size()),
																				outputcam.foundCorners,
																				cal_size,
																				outputcam.measured_k,outputcam.measured_d,tempR,tempT);
		
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
		fs<<configuration_.filename<<outputcam;
		fs.release();
		Success=true;
	}
	
	return Success;

}

bool SingleCalibrator::getCheckerBoard(cv::Mat input, std::vector< cv::Point2f >& output)
{
	/*find and store the checkerboard points*/
	bool found=cv::findChessboardCorners(input,
																	configuration_.getBoard(),output,
																  configuration_.getCalibrationFlags());
	return found;
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