#include "DataStructures/OutputData/ImageDetections.hpp"

namespace stereo {

ImageDetections::ImageDetections()
{

}

void ImageDetections::read(const cv::FileNode& node)
{

}


void ImageDetections::write(cv::FileStorage& fs) const
{
	
	/*write to xml files */
	fs<<"{";
	fs<<"imgDir"<<fullImgPath;
	fs<<"DetectedKP"<<"[";
	for(int index=0;index<detectedKP_.size();index++)
	{
		fs<<"{";
		fs<<"point"<<detectedKP_.at(index).pt;
		fs<<"size"<<detectedKP_.at(index).size;
		fs<<"angle"<<detectedKP_.at(index).angle;
		fs<<"response"<<detectedKP_.at(index).response;
		fs<<"octave"<<detectedKP_.at(index).octave;
		fs<<"id"<<detectedKP_.at(index).class_id;
		fs<<"}";
	}
	fs<<"]";
	fs<<"}";

}


}