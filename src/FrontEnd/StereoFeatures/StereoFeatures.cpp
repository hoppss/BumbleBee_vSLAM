#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

namespace stereo{

	
StereoFeatures::StereoFeatures()
{

}



void StereoFeatures::SimpleFeatures(cv::Mat image, std::vector< cv::KeyPoint >& output,StereoInternal settings_)
{
	/* No adjustments i.e. static thresholds, will implement limits on the number of points
	 * sent back if set*/
	settings_.detector_->getFeatures(image,output);
	if(settings_.internalOptions_&StereoInternal::ENFORCE_MAX_INITIAL_LIMIT)
	{
		getTopFeatures(output,settings_.maxInitialPoints_);
	}
	
}

void StereoFeatures::getFrame(StereoFrame& outputFrame, cv::Mat LeftIn, cv::Mat RightIn,StereoInternal settings_)
{
		//Assuming these are undistorted images, and the mapping functions exist
		//to the stereo rectified Images
	
	/* Extract the features in each image*/
	SimpleFeatures(LeftIn,outputFrame.leftKP_,settings_);
	SimpleFeatures(RightIn,outputFrame.rightKP_,settings_);
	
	//if preemptive rejection TODO

	settings_.descriptor_->compute(LeftIn,outputFrame.leftKP_,outputFrame.leftDescrip_);
	settings_.descriptor_->compute(RightIn,outputFrame.rightKP_,outputFrame.rightDescrip_);
	
	/*match them */
	switch(settings_.internalMatch_)
	{
		case StereoInternal::BRUTE_FORCE :
		{
			if(settings_.internalRobustness_|StereoInternal::CROSS_CHECK)
			{
				cv::BFMatcher matcher(settings_.getScoreMeasure(),true);
				matcher.match(outputFrame.leftDescrip_,outputFrame.rightDescrip_,outputFrame.matches_);
			}
			else
			{
				cv::BFMatcher matcher(settings_.getScoreMeasure(),false);
				matcher.match(outputFrame.leftDescrip_,outputFrame.rightDescrip_,outputFrame.matches_);
			}
			break;
		}
	}
	/* Perform robustness and pruning techniques */
	
	
	/*Calculate 3D Positions */
	

}


void StereoFeatures::getTopFeatures(std::vector< cv::KeyPoint >& output, int maxFeatures)
{
	std::sort(output.begin(),output.end(),[](cv::KeyPoint a, cv::KeyPoint b) { return a.response > b.response; });
	output.erase(output.begin()+maxFeatures,output.end());
}


void StereoFeatures::postRejection(StereoFrame& prunedFrame,cv::Mat fundamental)
{
	std::vector<cv::DMatch>::iterator current_match;
	current_match=prunedFrame.matches_.begin();
	while(current_match!=prunedFrame.matches_.end())
	{
		current_match++;
		current_match->distance;
		
		
	}
	
}






}