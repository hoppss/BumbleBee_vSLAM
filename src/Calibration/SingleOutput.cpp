#include "Calibration/SingleOutput.hpp"
#include <DataStructures/CameraInfo/Single.hpp>

namespace stereo
{

SingleOutput::SingleOutput()
{

}

void SingleOutput::read(const cv::FileNode& node)
{
	std::string mss;
	node["configuration"]>>conf_;
	node["rms"]>>rms_meas;
	node["k"]>>measured_k;
	node["d"]>>measured_d;
	node["cal"]>>calibration_size;
	cv::FileNodeIterator meas_begin,meas_end;
	meas_begin=node["Measurement"].begin();
	meas_end=node["Measurement"].end();
	std::string((*meas_begin)["nm"]);
	std::cout<<"sss ";//<<(*meas_begin)["nm"];
	//meas_it["nm"]>>static_cast<std::string>(mss);
	
	/*int temp;
	node["calFileName"]>>filename;
	node["inputDirectory"]>>in_directory;
	node["outDirectory"]>>out_directory;
	node["row"]>>patternRow;
	node["col"]>>patternCol;
	node["squareSize"]>>squareSize;
	node["units"]>>temp;
	unit=static_cast<SingleConfig::calUnits>(temp);
	node["debugInfo"]>>debugInfo;
	node["saveFound"]>>saveFou*/
}


void SingleOutput::write(cv::FileStorage& fs) const
{
	
	fs<<"{";
	fs<<"configuration"<<conf_;
	fs<<"rms"<<rms_meas;
	fs<<"k"<<measured_k;
	fs<<"d"<<measured_d;
	fs<<"cal"<<calibration_size;
	fs<<"Measurements"<<"[";
	for(int index=0;index<fullDirNames.size();index++)
	{
		fs<<"{";
		fs<<"nm"<<fullDirNames.at(index);
		fs<<"indiv"<<indivNames.at(index);
		fs<<"measured_points"<<"[";
		for(int pindex=0;pindex<foundCorners.at(index).size();pindex++)
		{
			fs<<"pt"<<foundCorners.at(index).at(pindex);
		}
		fs<<"]";
		fs<<"}";
	}
	fs<<"]";
	fs<<"}";

}



	
}