#include "Calibration/SingleOutput.hpp"
#include <DataStructures/CameraInfo/Single.hpp>

namespace stereo
{

SingleOutput::SingleOutput()
{

}

void SingleOutput::read(const cv::FileNode& node)
{
	node["configuration"]>>conf_;
	node["rms"]>>rms_meas;
	node["k"]>>measured_k;
	node["d"]>>measured_d;
	node["cal"]>>calibration_size;
	cv::FileNodeIterator meas_it,meas_end;
	meas_it=node["Measurements"].begin();
	meas_end=node["Measurements"].end();
	
	fullDirNames.clear();
	indivNames.clear();
	foundCorners.clear();
	for(;meas_it!=meas_end;++meas_it)
	{
		cv::FileNodeIterator point_it,point_end;
		std::string fulldir,indivN;
		
		point_it=(*meas_it)["measured_points"].begin();//assign the point iterator to the first element of measured points
		point_end=(*meas_it)["measured_points"].end(); //get the last element
		
		fulldir=std::string((*meas_it)["nm"]);//assign full directory of image
		indivN=std::string((*meas_it)["indiv"]);
		std::vector<cv::Point2f> foundPoints;//found points of the checkerboard for an individual image
		
		/*create a vector of found points */
		for(;point_it!=point_end;++point_it)
		{
			cv::Point2f tempPoint;
			(*point_it)>>tempPoint;
			foundPoints.push_back(tempPoint);
		}
		foundCorners.push_back(foundPoints);
		fullDirNames.push_back(fulldir);
		indivNames.push_back(indivN);
	}

}


void SingleOutput::write(cv::FileStorage& fs) const
{
	/*write to xml files */
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
			fs<<foundCorners.at(index).at(pindex);
		}
		fs<<"]";
		fs<<"}";
	}
	fs<<"]";
	fs<<"}";

}



	
}