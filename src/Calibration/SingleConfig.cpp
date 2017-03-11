#include "Calibration/SingleConfig.hpp"
#include <DataStructures/CameraInfo/Single.hpp>

namespace stereo
{

SingleConfig::SingleConfig()
{

}

void SingleConfig::write(cv::FileStorage& fs) const
{	
	/*write to XML */
	fs<<"{";
	fs<<"calFileName"<<filename;
	fs<<"inputDirectory"<<in_directory;
	fs<<"outDirectory"<<out_directory;
	fs<<"row"<<patternRow;
	fs<<"col"<<patternCol;
	fs<<"squareSize"<<squareSize;
	fs<<"units"<<static_cast<int>(unit);
	fs<<"debugInfo"<<debugInfo;
	fs<<"saveFound"<<saveFound;
	fs<<"saveNotFound"<<saveNotFound;
	fs<<"robust"<<robustCheckerBoard;
	fs<<"saveDrawn"<<saveDrawn;
	fs<<"displayFound"<<displayFound;
	fs<<"displayNotFound"<<displayNotFound;
	fs<<"displayUndistorted"<<displayUndistorted;
	fs<<"displayMapping"<<displayMapping;
	fs<<"cal_adapt"<<cal_adaptive;
	fs<<"cal_norm"<< cal_normalize;
	fs<<"cal_filter"<<cal_filter;
	fs<<"rational_model"<<compute_rational_model;
	fs<<"}";

}


void SingleConfig::read(const cv::FileNode& node)
{
	/*Read from XML*/
	int temp;
	node["calFileName"]>>filename;
	node["inputDirectory"]>>in_directory;
	node["outDirectory"]>>out_directory;
	node["row"]>>patternRow;
	node["col"]>>patternCol;
	node["squareSize"]>>squareSize;
	node["units"]>>temp;
	unit=static_cast<SingleConfig::calUnits>(temp);
	node["debugInfo"]>>debugInfo;
	node["saveFound"]>>saveFound;
	node["saveNotFound"]>>saveNotFound;
	node["robust"]>>robustCheckerBoard;
	node["saveDrawn"]>>saveDrawn;
	node["displayFound"]>>displayFound;
	node["displayNotFound"]>>displayNotFound;
	node["displayUndistorted"]>>displayUndistorted;
	node["displayMapping"]>>displayMapping;
	node["cal_adapt"]>>cal_adaptive;
	node["cal_norm"]>> cal_normalize;
	node["cal_filter"]>>cal_filter;
	node["rational_model"]>>compute_rational_model;
}

void SingleConfig::print()
{
	/*Small print out function for debug purposes*/
	std::cout<<"Output\t"<<filename<<std::endl;
	std::cout<<"ImageDirectory\t"<<in_directory<<std::endl;
	std::cout<<"OutputDirectory\t"<<out_directory<<std::endl;
	std::cout<<"patternRow\t"<<patternRow<<std::endl;
	std::cout<<"patternCol\t"<<patternCol<<std::endl;
	std::cout<<"patternSize\t"<<squareSize<<std::endl;	
	std::cout<<"Input Units\t";
	switch(unit)
	{
		case m :
		{
			std::cout<<"Meters (m)\n";
			break;
		}
		case cm :
		{
			std::cout<<"Centimeters (cm)\n";
			break;
		}
		case mm :
		{
			std::cout<<"Millimeters (mm)\n";
			break;
		}
	} 
	std::cout<<"Debug info\t"<<debugInfo<<std::endl;
	std::cout<<"saveFound\t"<<saveFound<<std::endl;
	std::cout<<"saveNotFound\t"<<saveNotFound<<std::endl;
	std::cout<<"displayUndistort\t"<<displayUndistorted<<std::endl;
	std::cout<<"displayMap\t"<<displayMapping<<std::endl;
	std::cout<<"robustCheckerBoard\t"<<robustCheckerBoard<<std::endl;
	std::cout<<"saveDrawn\t"<<saveDrawn<<std::endl;
	std::cout<<"displayNotFound\t"<<displayNotFound<<std::endl;
	std::cout<<"displayFound\t"<<displayFound<<std::endl;
	std::cout<<"cal_adapt\t"<<cal_adaptive<<std::endl;
	std::cout<<"cal_norm\t"<<cal_normalize<<std::endl;
	std::cout<<"cal_filter\t"<<cal_filter<<std::endl;
	std::cout<<"rational_model\t"<<compute_rational_model<<std::endl;
}

cv::Size SingleConfig::getBoard()
{
	/*returns the inner board size of the checkerboard*/
	return cv::Size(patternRow-1,patternCol-1);
}

int SingleConfig::getCalibrationFlags()
{
	/*combines all the calibration flags into one single number to be 
	 * passed to opencv calibrate function*/
	int flags= 0;
	if(cal_adaptive)
	{
		flags+=CV_CALIB_CB_ADAPTIVE_THRESH;
	}
	if(cal_filter)
	{
		flags+=CV_CALIB_CB_FILTER_QUADS;
	}
	if(cal_normalize)
	{
		flags+=CV_CALIB_CB_NORMALIZE_IMAGE;
	}
	if(compute_rational_model)
	{
		flags+=CV_CALIB_RATIONAL_MODEL;
	}
	return flags;
}

std::vector< cv::Point3f > SingleConfig::genBoardCoordinate()
{
	return getChessPoints(getBoard(),squareSize,1).at(0);
}


std::vector< std::vector< cv::Point3f > > SingleConfig::genSetBoardCoordinate(int image_total)
{
	
	return getChessPoints(getBoard(),squareSize,image_total);

}


std::vector< std::vector< cv::Point3f > > getChessPoints(cv::Size board, double square_size, int n)
{
	/*produces a vector of chesspoints relative to the checkerboard, requires the size of the inner board,
	 * the physical dimensions of the squares used in the calibration,
	 * and the total number of copies n to be made*/
	std::vector< std::vector< cv::Point3f > > Ans;
	
	for(int pattern=0;pattern<n;pattern++)
	{
		std::vector< cv::Point3f > singleBoard;
		for(int row=0;row<board.height;row++)
		{
			for(int col=0;col<board.width;col++)
			{
				cv::Point3f tempPoint;
				tempPoint.x=col*square_size;
				tempPoint.y=row*square_size;
				tempPoint.z=0;
				singleBoard.push_back(tempPoint);
			}
		}
		Ans.push_back(singleBoard);
	}
	return Ans;

}








}