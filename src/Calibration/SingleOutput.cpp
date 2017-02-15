#include "Calibration/SingleOutput.hpp"
#include <DataStructures/CameraInfo/Single.hpp>

namespace stereo
{

SingleOutput::SingleOutput()
{
	file_prefix="file_";
	output_folder="output";
	debug_folder="debug";
	debugConfiguration=0;
	
}

void SingleOutput::debugOut(std::string message)
{
	if(debugConfiguration&debugInfo)
	{
		std::cout<<message<<std::endl;
	}
}



void SingleOutput::setMetaData(std::string file, std::string output, std::string debug)
{
	file_prefix=file;
	output_folder=output;
	debug_folder=debug;
}

bool SingleOutput::calibrate()
{

}

bool SingleOutput::calibrateCamera(std::string mainDir, int row, int col, int size, int un)
{
	debugConfiguration=0;
	board_row=row;
	board_column=col;
	size_square=size;
	unit=un;
	printDebugConfig();
}

bool SingleOutput::calibrateCamera(std::string mainDir, int row, int col, int size, int un, int conf)
{
	clearInternals();
	bool Success;
	debugConfiguration=conf;
	board_row=row;
	board_column=col;
	size_square=size;
	unit=un;
	printDebugConfig();
	if(getImageList(mainDir))
	{
		genFeatures();
		Success=true;
	}
	else
	{
		Success=false;
	}
	
	return Success;
}

void SingleOutput::findImageFeature(cv::Mat img)
{
	std::stringstream err;
	bool found;
	std::vector<cv::Point2f> imageCorners;
	
	found=cv::findChessboardCorners(img,
																	internalBoardSize,imageCorners,
																 cv::CALIB_CB_ADAPTIVE_THRESH|cv::CALIB_CB_NORMALIZE_IMAGE|cv::CALIB_CB_FILTER_QUADS);
	err<<"found checkerboard==" <<found;
	debugOut(err.str());
	

	if(found)
	{
			foundCorners.push_back(imageCorners);
			//draw chessboard on image and save it
			cv::Mat output;
			cv::cvtColor(img,output,cv::COLOR_GRAY2BGR);
			cv::drawChessboardCorners(output,internalBoardSize,imageCorners,true);
			outputImages.push_back(output);
			
			if(debugConfiguration&displayOut)
			{
					cv::namedWindow("checkerboard",CV_WINDOW_NORMAL);
					cv::imshow("checkerboard",output);
			}
			if(debugConfiguration&saveFound)
			{
				std::stringstream ss;
			}
			
	}
	else
	{
			if(debugConfiguration&displayNotFound)
			{
				cv::namedWindow("notFound",CV_WINDOW_NORMAL);
				cv::imshow("notFound",img);
			}
			if(debugConfiguration&saveNotFound)
			{
			}
	}
	
	if((debugConfiguration&displayNotFound)||(debugConfiguration&displayOut))
	{
		cv::waitKey(0);
		cv::destroyAllWindows();
	}

}

void SingleOutput::createDir(std::string dir)
{
	
	
	std::stringstream comm;
	
	comm<<"mkdir -p "<<dir;
	
	std::string a=comm.str();
	system(a.c_str());
}



void SingleOutput::genFeatures()
{
	calibration_size=inputImages.at(0).size();
	internalBoardSize=cv::Size(board_row-1,board_column-1);
	std::cout<<"Image processing Progress -- \n";
	
	for(int imageIndex=0;imageIndex<inputImages.size();imageIndex++)
		{
			std::cout<<indivNames.at(imageIndex)<<" -- ["<<(imageIndex+1)<<"/"<<inputImages.size()<<"]\t";
			findImageFeature(inputImages.at(imageIndex));
			
			
				/*found=cv::findChessboardCorners(inputImages.at(imageIndex),board,tempCorners,cv::CALIB_CB_ADAPTIVE_THRESH|cv::CALIB_CB_NORMALIZE_IMAGE|cv::CALIB_CB_FILTER_QUADS);
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
					if(showNotFound)
					{
						cv::namedWindow("NotFound",cv::WINDOW_NORMAL);
						cv::imshow("NotFound",inputImages.at(imageIndex));
						cv::waitKey(0);	
						cv::destroyWindow("NotFound");
					}
				}	
	*/
		}
}

void SingleOutput::printDebugConfig()
{
	std::cout<<"Debug Settings\n______________\n";
//	std::cout<<"debug info- "<<std::bitset<7>(debugConfiguration)<<std::endl;
	if(debugConfiguration==0)
	{
		std::cout<<"Debug off\n";
	}

	if(debugConfiguration&displayOut)
	{
		std::cout<<"Displaying output images\n";
	}
	if(debugConfiguration&saveFound)
	{
		std::cout<<"Saving Checkerboard Images\n";
	}
	if(debugConfiguration&debugInfo)
	{
		std::cout<<"Debug Information\n";
	}
	if(debugConfiguration&displayNotFound)
	{
		std::cout<<"Displaying Not Found images\n";
	}
	if(debugConfiguration&saveNotFound)
	{
		std::cout<<"Saving Images Not Found\n";
	}
	
	std::cout<<"____________\n";
}

bool SingleOutput::getImageList(std::string mainDir)
{
	bool Success;
	DIR *dp;
	struct dirent *dirp;
	if((dp=opendir(mainDir.c_str())) == NULL)
	{
		std::cerr << "Error(" << errno << ") opening " <<mainDir<< std::endl;
		Success=false;
	}
	else
	{
		debugOut("Reading from MainDir");
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
				
				indivNames.push_back(tempname);
				//Load image
				std::string full_dir;
				
				full_dir=mainDir;
				full_dir+="/";
				full_dir+=tempname;
				
				fullNames.push_back(full_dir);
				
				cv::Mat tempImage=cv::imread(full_dir,cv::IMREAD_GRAYSCALE);
				
				inputImages.push_back(tempImage);
				debugOut("Reading - "+full_dir);
			}

		}
		closedir(dp);
		
		
		if((fullNames.size()<1)||(indivNames.size()<1))
		{
			std::cerr<<"No image files found under "<<mainDir<<std::endl;
			Success=false;
		}
		else
		{
			//create Directories
			
			if(debugConfiguration&saveFound)
			{
				std::stringstream full;
				full<<mainDir<<"/"<<debug_folder<<"/Found";
				createDir(full.str());
			}
			if(debugConfiguration&saveNotFound)
			{
				std::stringstream full;
				full<<mainDir<<"/"<<debug_folder<<"/NotFound";
				createDir(full.str());
			}
			
			Success=true;
		}
	}
	
	return Success;
}

void SingleOutput::clearInternals()
{
	fullNames.clear();
	indivNames.clear();
	inputImages.clear();
	outputImages.clear();
	foundCorners.clear();
}


	
}