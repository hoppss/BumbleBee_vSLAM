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
	//	Stereo calibration_;
	public:
		StereoInternal();
		enum MatchMethod
		{
			BRUTE_FORCE=1<<0,
			RADIUS=1<<1, //note it is radius in terms of matching score, not geometric distance
			KNN_MATCH=1<<2
		};
		enum RobustnessCriteria
		{
			PREEMPTIVE_REJECTION=1<<0,//reject features using epi poles before description
			CROSS_CHECK=1<<1,
						/*only accept features where the best match is each other ft1
			 *closest match is ft2, and ft2 closest match is ft1*/ 
			POST_REJECTION=1<<2,//reject Features using epi poles post description
			PRUNE_INITIAL_SCORE=1<<3//reject initial features according to score if detected points exceeds maxInitialPoints_;
		};
		enum DescriptionMethod
		{
			BRIEF_DESCR=1<<0, //indicates which Norm to use during the matching
		};
		enum ComputeStatistics
		{
			DETECTION_TIME=1<<0,//overall
			CELL_DETECTION_TIME=1<<1,//for each grid cell
			DESCRIPTION_TIME=1<<2,
			CELL_DESCRIPTION_TIME=1<<3,
			OVERALL_TIME=1<<4,
			ADMIN_TIME=1<<5,//compute how much time is used switching into and out of functions
			KEEP_OUTLIER=1<<6, //save the features that were removed as outliers
			KEEP_PROGRESS=1<<7,
			KEEP_RECTIFIED=1<<8,
		};
		enum DetectionOptions
		{
			SIMPLE=1<<0,
			BRUTE=1<<1,
			GRIDDED=1<<2,
			ADAPTIVE=1<<3
			//TODO search only along rows for matching descriptors
		};
		//image processing settings
		std::shared_ptr<DetSettings> default_detector_;
		cv::Ptr<cv::DescriptorExtractor> default_descriptor_;
		float maxRadius_;
		float epiThresh_;//distance in pixels a point is considered an outlier from the epipolar line
		int maxInitialPoints_;
		int n_rows,n_cols;
		int min_thresh_,max_thresh_;
		//stereo camera settings
		MatchMethod internalMatch_;
		RobustnessCriteria internalRobustness_;
		DescriptionMethod internalDescription_;
		ComputeStatistics internalStatistics_;
		DetectionOptions internalDetectionOptions_;
		/**configuration and loading functions*/
	//	void setCameraInfo(Stereo configuration);
	//	void setCameraInfo(std::string configuration_xml);
		int getScoreMeasure();		
	protected:
		bool initialized_;
		bool validMatchMethod();
		bool validRobustnessCriteria();
		bool validDescription();
		bool validStats();
};
}


#endif