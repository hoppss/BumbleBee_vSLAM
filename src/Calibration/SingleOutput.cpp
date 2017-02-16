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


bool SingleOutput::calibrateCamera(std::string mainDir,std::string outputDir, int row, int col, int size, int un)
{
	debugConfiguration=0;
	board_row=row;
	board_column=col;
	size_square=size;
	unit=un;
	setDirectories(mainDir,outputDir);
	printDebugConfig();
}

void SingleOutput::setDirectories(std::string in, std::string out)
{
	std::stringstream dir;
	dir<<out<<"/"<<output_folder;
	inputDir=in;
	outputDir=dir.str();
}


bool SingleOutput::calibrateCamera(std::string mainDir,std::string outputDir, int row, int col, int size, int un, int conf)
{
	clearInternals();
	bool Success;
	debugConfiguration=conf;
	board_row=row;
	board_column=col;
	size_square=size;
	unit=un;
	setDirectories(mainDir,outputDir);
	printDebugConfig();
	if(getImageList(mainDir))
	{
		genFeatures();
		debugOut("Finished Feature Gen");
		Success=true;
	}
	else
	{
		Success=false;
	}
	
	return Success;
}

void SingleOutput::findImageFeature(cv::Mat img,std::string fname)
{
	std::stringstream err;
	bool found;
	std::vector<cv::Point2f> imageCorners;
	
	found=cv::findChessboardCorners(img,
																	internalBoardSize,imageCorners,
																 cv::CALIB_CB_ADAPTIVE_THRESH|cv::CALIB_CB_NORMALIZE_IMAGE);
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
				std::stringstream pic_dir;
				pic_dir<<outputDir<<"/"<<debug_folder<<"/Found/"<<file_prefix<<fname;
				err.clear();
				err<<"\tsaving \t"<<pic_dir.str();
				debugOut(err.str());
				
				cv::imwrite(pic_dir.str(),output);
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
				std::stringstream pic_dir;
				pic_dir<<outputDir<<"/"<<debug_folder<<"/NotFound/"<<file_prefix<<fname;
				err.clear();
				err<<"\tsaving \t"<<pic_dir.str();
				debugOut(err.str());
				
				cv::imwrite(pic_dir.str(),img);
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

std::vector< std::vector< cv::Vec3f > > SingleOutput::generateCheckBoardCoord()
{
	std::vector< std::vector< cv::Vec3f > > Ans;
	
	for(int pattern=0;pattern<outputImages.size();pattern++)
	{
		std::vector< cv::Vec3f > singleBoard;
		for(int row=0;row<internalBoardSize.height;row++)
		{
			for(int col=0;col<internalBoardSize.width;col++)
			{
				cv::Vec3f tempPoint;
				tempPoint[0]=col*size_square;
				tempPoint[1]=row*size_square;
				tempPoint[2]=0;
				singleBoard.push_back(tempPoint);
			}
		}
		Ans.push_back(singleBoard);
	}
	return Ans;

}




void SingleOutput::genFeatures()
{
	calibration_size=inputImages.at(0).size();
	internalBoardSize=cv::Size(board_row-1,board_column-1);
	std::cout<<"Image processing Progress -- \n";
	
	for(int imageIndex=0;imageIndex<inputImages.size();imageIndex++)
		{
			std::cout<<indivNames.at(imageIndex)<<" -- ["<<(imageIndex+1)<<"/"<<inputImages.size()<<"]\t";
			findImageFeature(inputImages.at(imageIndex),indivNames.at(imageIndex));
		}
	std::cout<<"Images Processed -- calculating calibration\n";
	std::vector<cv::Mat> tempR,tempT;
	rms_meas=cv::calibrateCamera(generateCheckBoardCoord(),foundCorners,calibration_size,measured_k,measured_d,tempR,tempT,CV_CALIB_RATIONAL_MODEL);
	
	std::stringstream err;
	err<<"Rms Error of calibration : "<<rms_meas;
	debugOut(err.str());
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
			}

		}
		closedir(dp);
		
		std::sort(indivNames.begin(),indivNames.end());
		
		loadImages();
		
		
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
				full<<outputDir<<"/"<<debug_folder<<"/Found";
				createDir(full.str());
				debugOut(full.str());
				
			}
			if(debugConfiguration&saveNotFound)
			{
				std::stringstream full;
				full<<outputDir<<"/"<<debug_folder<<"/NotFound";
				createDir(full.str());
				debugOut(full.str());
			}
			
			Success=true;
		}
	}
	
	return Success;
}

void SingleOutput::loadImages()
{
	for(int index=0;index<indivNames.size();index++)
	{
		
		std::string full_dir;
				
		full_dir=inputDir;
		full_dir+="/";
		full_dir+=indivNames.at(index);
				
		fullNames.push_back(full_dir);
		
		cv::Mat tempImage=cv::imread(full_dir,cv::IMREAD_GRAYSCALE);
				
		inputImages.push_back(tempImage);
		debugOut("Reading - "+full_dir);
		
	}
}

void SingleOutput::clearInternals()
{
	fullNames.clear();
	indivNames.clear();
	inputImages.clear();
	outputImages.clear();
	foundCorners.clear();
}

void SingleOutput::printConfig()
{
	std::cout<<"K "<<measured_k<<std::endl;
	std::cout<<"D "<<measured_d<<std::endl;
	std::cout<<"Rms "<<rms_meas<<std::endl;
}


Single SingleOutput::generateSingle()
{
	Single ans;
	ans.K_=measured_k;
	ans.K_dist_=measured_d;
	ans.RMS_Error=rms_meas;
}



	
}