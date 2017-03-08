#ifndef STEREO_FEATURES_HEADER_HPP
#define STEREO_FEATURES_HEADER_HPP
#include "DataStructures/CameraInfo/Stereo.hpp"
#include "FrontEnd/Detection/BRISKdet.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <memory>


namespace stereo
{
class StereoFeatures
{
	private:
		bool initialized_;
		Stereo calibration_;
	public:
		StereoFeatures();
		StereoFeatures(Stereo configuration);
		StereoFeatures(std::string  directory);
		void setConfiguration(std::string directory);
		void setConfiguration(Stereo configuration);
		void setInternal(DetSettings *ptr_detector,
										 cv::Ptr<cv::DescriptorExtractor> ptr_descr);
};
	
}

#endif