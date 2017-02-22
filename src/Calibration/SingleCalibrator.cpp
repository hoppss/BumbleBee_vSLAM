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
	std::stringstream comm;
	std::stringstream fulldir;
	std::string str_command;
	
	msgs_.str("");
	msgs_<<"Directories created\t";
	
	if(configuration_.saveFound)
	{
		fulldir.str("");
		fulldir<<configuration_.out_directory<<"/Found";
		comm.str("");
		comm<<"mkdir -p "<<fulldir.str();
		str_command=comm.str();
		system(str_command.c_str());
		full_found=fulldir.str();
		msgs_<<fulldir.str()<<"\t";
	}
	if(configuration_.saveNotFound)
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
	
	
	if(configuration_.saveDrawn)
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
	outputcam.foundCorners.clear();
	outputcam.fullDirNames.clear();
	outputcam.indivNames.clear();
	cv::Size cal_size;
	tempNames.clear();
	bool Success;
	Success=genImageList();
	if(Success)
	{
		genDirectories();
		std::cout<<"finding corners\n";
		for(int dirIndex=0;dirIndex<tempNames.size();dirIndex++)
		{
			std::cout<<"["<<dirIndex+1<<"/"<<tempNames.size()<<"]\n";
			cv::Mat currentInput,checkerBoard;
			getImage(dirIndex,currentInput);
			cal_size=currentInput.size();
			std::vector<cv::Point2f> currentFoundPoints;
			bool found=getCheckerBoard(currentInput,currentFoundPoints);
			msgs_.str("");
			msgs_<<"found checkerboard = "<<found<<"\t Image:\t"<<tempNames.at(dirIndex);
			debugOut(msgs_.str(),true);
			
			
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
					std::string dirname=full_drawn;
					dirname+="/";
					dirname+=tempNames.at(dirIndex);
					cv::imwrite(dirname,checkerBoard);
				}
				if(configuration_.saveFound)
				{
					std::string dirname=full_found;
					dirname+="/";
					dirname+=tempNames.at(dirIndex);
					cv::imwrite(dirname,currentInput);
				}
				
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
				cv::waitKey(0);
				cv::destroyAllWindows();
			}
			
			
		}
		
		//calibrate camera
		
		std::vector<cv::Mat> tempR,tempT;
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
	bool found=cv::findChessboardCorners(input,
																	configuration_.getBoard(),output,
																  configuration_.getCalibrationFlags());
	return found;
}



bool SingleCalibrator::genImageList()
{
	bool Success=false;
	DIR *dp;
	struct dirent *dirp;
	if((dp=opendir(configuration_.in_directory.c_str())) == NULL)
	{
		std::cerr << "Error(" << errno << ") opening " <<configuration_.in_directory<< std::endl;
		Success=false;
	}
	else
	{
		debugOut("Reading from MainDir",true);
		while( (dirp=readdir(dp))!= NULL)
			{
				std::string readname(dirp->d_name);
				bool reject=false;
				if((readname.compare("..")==0)||(readname.compare(".")==0))
				{
					reject=true;
				}
			
				if(!reject)//gets rid of the .  and .. directories
				{
					tempNames.push_back(readname);
				}

			}
		closedir(dp);
		std::sort(tempNames.begin(),tempNames.end());
		Success=true;
	}
	return Success;
}



void SingleCalibrator::debugOut(std::string msg, bool newline)
{
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
	std::stringstream inputFile;
	inputFile<<configuration_.in_directory<<"/"<<tempNames.at(index);
	output=cv::imread(inputFile.str(),cv::IMREAD_GRAYSCALE);
	msgs_.str("");
	msgs_<<"Loaded Image "<<inputFile.str();
	debugOut(msgs_.str(),true);
}








	
}