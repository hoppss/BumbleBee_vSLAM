#ifndef DATASTRUCTURES_IMAGE_DETECTIONS_HEADER_HPP
#define DATASTRUCTURES_IMAGE_DETECTIONS_HEADER_HPP

#include <iostream>
#include <opencv2/features2d.hpp>

namespace stereo
{
	
class ImageDetections
{
	public:
		ImageDetections();
		std::string fullImgPath;
		std::vector<cv::KeyPoint> detectedKP_;
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);

};


//These write and read functions must be defined for the serialization in FileStorage to work
static void write(cv::FileStorage& fs, const std::string&, const ImageDetections& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, ImageDetections& x, const ImageDetections& default_value = ImageDetections()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

}

#endif