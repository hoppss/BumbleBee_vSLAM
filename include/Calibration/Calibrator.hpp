#ifndef CALIBRATOR_HEADER_HPP
#define CALIBRATOR_HEADER_HPP

#include <algorithm>
#include <vector>


#include <cstdlib>
#include <highgui.h>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>

#include "DataStructures/CameraInfo/Stereo.hpp"

namespace stereo{
	
	enum CalibratorDEBUG
	{
		displayBoards=1<<0,
		saveFoundBoards=1<<1,
		debugLeft=1<<2,
		debugRight=1<<3,
		debugOutput=1<<4,
		displayNotFound=1<<5
	};

	class Calibrator
	{
		private:
			bool debugInfo;
			bool showNotFound;
			bool getImageList(std::string subDirectory, std::vector< cv::Mat >& output);
			bool calibrate(std::string mainDir,
										 std::vector< cv::Mat > &inputImages,
										 std::vector< cv::Mat > &outputImages,
										 cv::Mat &K,cv::Mat &D,
									   double &rms,int row,int col, int size);
			void displayImg(std::vector< cv::Mat > img);
			std::vector< std::vector< cv::Vec3f > > genBoardPoints(cv::Size board, int square_size,int PatternViews);
		public:
			Calibrator();
			Single calibrateCamera(std::string mainDir,int row,int col, int size);
			Single calibrateCamera(std::string mainDir,int config,std::string output,int row,int col, int size);
			
	};
	
		
		
}


#endif