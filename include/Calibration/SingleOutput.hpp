#ifndef SINGLE_OUTPUT_HEADER_HPP
#define SINGLE_OUTPUT_HEADER_HPP

#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <cstdlib>
#include <highgui.h>


#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>


#include <iostream>
#include <bitset>
namespace stereo
{
	
class SingleOutput
{
	private:
		//metadata
		int debugConfiguration;
		std::string file_prefix;
		std::string inputDir;
		std::string outputDir;
		std::string output_folder;
		std::string debug_folder;
		int board_row,board_column;
		int size_square;
		int unit;
		std::vector<std::string> fullNames,indivNames; 
		//metadata
		///////data
		std::vector<cv::Mat> inputImages,outputImages;
		std::vector< std::vector<cv::Point2f> > foundCorners;
		double rms_meas;
		cv::Mat measured_k;
		cv::Mat measured_d;
		cv::Size calibration_size;
		cv::Size internalBoardSize;
		////data
		void debugOut(std::string message);
		bool calibrate();
		void printDebugConfig();
		bool getImageList(std::string mainDir);
		void genFeatures();
		void clearInternals();
		void findImageFeature(cv::Mat img,std::string fname);
		void createDir(std::string dir);
		void setDirectories(std::string in,std::string out);
		std::vector< std::vector< cv::Vec3f > > generateCheckBoardCoord();
		
	//	std::vector< std::vector< cv::Vec3f > > genBoardPoints(cv::Size board, int square_size,int PatternViews);
	public:
		enum SingleOutputDEBUG
		{
			displayOut=1<<1,
			saveFound=1<<2,
			saveNotFound=1<<3,
			debugInfo=1<<4,
			displayNotFound=1<<5
		};
		enum calUnits
		{
			m,
			cm,
			mm
		};
		SingleOutput();
		void setMetaData(std::string file,std::string output,std::string debug);
		bool calibrateCamera(std::string mainDir,std::string outputDir,int row,int col, int size,int un);
		bool calibrateCamera(std::string mainDir,std::string outputDir,int row,int col, int size,int un,int conf);
		void printConfig();
	
};

}



#endif