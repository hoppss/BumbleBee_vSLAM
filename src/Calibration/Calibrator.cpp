#include <Calibration/Calibrator.hpp>

namespace stereo
{

Calibrator::Calibrator()
{
	debugInfo=false;
}


bool Calibrator::calibrate(std::string mainDir, std::vector< cv::Mat >& inputImages, std::vector< cv::Mat >& outputImages, double& rms,int row,int col, int size)
{
	bool Success;
	cv::Size board(row-1,col-1);
	std::vector< std::vector<cv::Point2f> > corners; //holds all the corners found over set of images
	std::vector< std::vector<cv::Point3f> > boardPoints;
	cv::Size calibration_size;
	
	
	
	
	
	if(getImageList(mainDir,inputImages))
	{		
		calibration_size=inputImages.at(0).size();
		
		for(int imageIndex=0;imageIndex<inputImages.size();imageIndex++)
		{
			
			if(debugInfo)
			{
				std::cout<<"Find corners for image "<<imageIndex<<std::endl;
			}
			

				bool found;
				std::vector<cv::Point2f> tempCorners;
				found=cv::findChessboardCorners(inputImages.at(imageIndex),board,tempCorners,cv::CALIB_CB_ADAPTIVE_THRESH|cv::CALIB_CB_NORMALIZE_IMAGE|cv::CALIB_CB_FILTER_QUADS);
				if(found)
				{
					if(debugInfo)
					{
						std::cout<<"Corners Found "<<imageIndex<<std::endl;
					}
					corners.push_back(tempCorners);
					//draw chessboard on image and save it
					cv::Mat output;
					cv::cvtColor(inputImages.at(imageIndex),output,cv::COLOR_GRAY2BGR);
					cv::drawChessboardCorners(output,board,tempCorners,true);
					outputImages.push_back(output);
				}
				else
				{
				std::cout<<"no chessboard found for image with index = " <<imageIndex<<std::endl;
				}			
	}

	//		double rms_temp;
	//		cv::Mat tempK,tempD;
	//		std::vector<cv::Mat> tempR,tempT;
			
	//		rms_temp=cv::calibrateCamera(genBoardPoints(board,squareSize,left_images.size()),leftCorners,calibration_size,tempK,tempD,tempR,tempT,CV_CALIB_RATIONAL_MODEL);
			
			
		
		
		
		Success=true;
	}
	else
	{
		std::cerr<<"Image List failed to load"<<std::endl;
		Success=false;
	}
	return Success;
}


Single Calibrator::calibrateCamera(std::string mainDir,int row,int col, int size)
{
	Single Ans;
	std::vector< cv::Mat > in,out;
	double rms;
	if(calibrate(mainDir,in,out,rms,row,col,size))
	{
	}
	
	return Ans;
	
}


Single Calibrator::calibrateCamera(std::string mainDir, int config,std::string output,int row,int col, int size)
{
	
	if((config&debugOutput))
	{
		debugInfo=true;
	}
	else
	{
		debugInfo=false;
	}
	
	Single Ans;
	std::vector< cv::Mat > in,out;
	double rms;
	
	if(calibrate(mainDir,in,out,rms,row,col,size))
	{
		
		if(displayBoards&config)
		{
			displayImg(out);
		}
	}
	
	return Ans;
}



bool Calibrator::getImageList(std::string subDirectory, std::vector< cv::Mat >& output)
{
	bool Success;
	DIR *dp;
	struct dirent *dirp;
	if((dp=opendir(subDirectory.c_str())) == NULL)
	{
		std::cerr << "Error(" << errno << ") opening " <<subDirectory<< std::endl;
		Success=false;
	}
	else
	{
		if(debugInfo)
		{
			std::cout<<"Reading from Dir : "<<subDirectory<<std::endl;
		}
		
		while( (dirp=readdir(dp))!= NULL)
		{
			
			std::string tempname(dirp->d_name);
			bool reject=false;
			if((tempname.compare("..")==0)||(tempname.compare(".")==0))
			{
				reject=true;
			}
			
			if(!reject)//gets rid of the .  and .. directories
			{
				//Load image
				std::string full_dir;
				
				full_dir=subDirectory;
				full_dir+="/";
				full_dir+=tempname;
				
				cv::Mat tempImage=cv::imread(full_dir,cv::IMREAD_GRAYSCALE);
				
				output.push_back(tempImage);
			}

		}
		closedir(dp);
		Success=true;
		
	}
	
	return Success;
}


void Calibrator::displayImg(std::vector< cv::Mat > img)
{
	cv::namedWindow("output",cv::WINDOW_NORMAL);
	for(int index=0;index<img.size();index++)
	{
			cv::imshow("output",img.at(index));
			cv::waitKey(0);	
	}
	cv::destroyWindow("output");
}





	
}