#ifndef STEREO_INTERNAL_HEADER_HPP
#define STEREO_INTERNAL_HEADER_HPP_

#include "FrontEnd/Detection/BRISKdet.hpp"
#include "DataStructures/CameraInfo/Stereo.hpp"

#include <memory>
/**
 * Holds all of the stereo internal settings such as robustness checks to apply,
 * match methods, etc..*/
namespace stereo
{

class StereoInternal
{
	private:
		bool initialized_;
		Stereo calibration_;
	public:
		StereoInternal();
		enum MatchMethod
		{
			BRUTE_FORCE,
			RADIUS, //note it is radius in terms of matching score, not geometric distance
			KNN_MATCH,
		};
		enum RobustnessCriteria
		{
			PREEMPTIVE_REJECTION=1<<0,//reject features using epi poles before description
			CROSS_CHECK=1<<1,
			POST_REJECTION=1<<2,//reject Features using epi poles post description
			/*only accept features where the best match is each other ft1
			 *closest match is ft2, and ft2 closest match is ft1*/ 
		};
		enum DescriptionMethod
		{
			BRIEF_DESCR, //indicates which Norm to use during the matching
		};
		enum ComputeStatistics
		{
			DETECTION_TIME=1<<0,//overall
			CELL_DETECTION_TIME=1<<1,//for each grid cell
			DESCRIPTION_TIME=1<<2,
			CELL_DESCRIPTION_TIME=1<<3,
			OVERALL_TIME=1<<4,
			ADMIN_TIME=1<<5,//compute how much time is used switching into and out of functions
		};
		enum Options
		{
			UNDISTORT_IMAGE=1<<0,
			STEREO_RECTIFY_IMAGE=1<<1,
			ENFORCE_MAX_INITIAL_LIMIT=1<<2 //on first detect, will sort by best initialPoints, and discarded any extra
		};
		//image processing settings
		std::shared_ptr<DetSettings> detector_;
		cv::Ptr<cv::DescriptorExtractor> descriptor_;
		float maxRadius_;
		int maxInitialPoints_;
		//stereo camera settings
		MatchMethod internalMatch_;
		RobustnessCriteria internalRobustness_;
		DescriptionMethod internalDescription_;
		ComputeStatistics internalStatistics_;
		Options internalOptions_;
		/**configuration and loading functions*/
		void setCameraInfo(Stereo configuration);
		void setCameraInfo(std::string configuration_xml);
		int getScoreMeasure();
		
		
		
};
}


#endif