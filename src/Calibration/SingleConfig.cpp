#include "Calibration/SingleConfig.hpp"
#include <DataStructures/CameraInfo/Single.hpp>

namespace stereo
{

SingleConfig::SingleConfig()
{

}

void SingleConfig::write(cv::FileStorage& fs) const
{	
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
	fs<<"}";

}


void SingleConfig::read(const cv::FileNode& node)
{

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

}

void SingleConfig::print()
{
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
}





}