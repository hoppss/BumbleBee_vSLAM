
#include "FrontEnd/StereoFeatures/StereoRectifiedFeatures.hpp"

namespace stereo

{

StereoRectifiedFeatures::StereoRectifiedFeatures() : StereoRectifiedInternal()
{

}

bool StereoRectifiedFeatures::Initialize_(std::string directoryXML)
{
	/*extracts all the settings required, and setups any grids/adapters*/
	if(LoadCameraSettings(directoryXML))
	{
		/*check other settings have been set correctly*/
		if(checkSettings())
		{
			
			if((!default_descriptor_.empty())||(default_detector_!= nullptr))
			{
				/*TODO Create different grid detectors*/
				/*TODO set ROI on images*/
				std::cout<<"success: StereoFeatures Initialized";
				initialized_=true;
			}
			else
			{
				std::cout<<"no detector/descriptor objected detected"<<std::endl;
				initialized_=false;
			}
		}
		else
		{
			std::cout<<"error: input settings have not been set"<<std::endl;
			initialized_=false;
		}
	}
	else
	{
		initialized_=false;
	}	
	return initialized_;
}

bool StereoRectifiedFeatures::checkSettings()
{
	bool Success=false;
	if(validMatchMethod())
	{
		if(validRobustnessCriteria())
		{
			if(validDescription())
			{
				if(validStats())
				{
					Success=true;
				}
			}
		}
		
	}
	
	return Success;
}



void StereoRectifiedFeatures::getFrame(StereoFrame& outputFrame, cv::Mat LeftIn, cv::Mat RightIn)
{
	if((internalDetectionOptions_&StereoInternal::DetectionOptions::SIMPLE))
	{
		SimpleFrame(outputFrame,LeftIn,RightIn);
	}
}

void StereoRectifiedFeatures::SimpleFrame(StereoFrame& outputFrame, cv::Mat LeftIn, cv::Mat RightIn)
{
	cv::Mat outimage,outimage2;//remove
	StereoRectifiedFeedback feed(ptr_cal_);
	
	cv::Mat lRectified,rRectified;
	lRectified=cv::Mat(ptr_cal_->L_fMapx_.size(),LeftIn.type());
	rRectified=cv::Mat(ptr_cal_->R_fMapx_.size(),RightIn.type());
	
	cv::remap(LeftIn,lRectified,ptr_cal_->L_fMapx_,ptr_cal_->L_fMapy_,cv::INTER_LINEAR);
	cv::remap(RightIn,rRectified,ptr_cal_->R_fMapx_,ptr_cal_->R_fMapy_,cv::INTER_LINEAR);

	
	/*rectify the left and right images, includes black space and is the same size as the original image,
	 * with ROI already computed*/
	cv::Mat limg(lRectified,ptr_cal_->l_ROI_),rimg(rRectified,ptr_cal_->r_ROI_);//set ROI 
	
	
	//dertect features in each region of interest according to the detecion method and settings
	//in this case, it uses default settings throughout the run (no adaptive no modifications from initial
	//setup)
	default_detector_->getFeatures(limg,outputFrame.leftKP_);
	default_detector_->getFeatures(rimg,outputFrame.rightKP_);

	if(internalRobustness_&StereoInternal::PRUNE_INITIAL_SCORE)
	{
		//only keep the maxInitialPoints with the Highest detector scores
		if(internalStatistics_&StereoInternal::KEEP_OUTLIER)
		{
			pruneTopScores(outputFrame.leftKP_,outputFrame.statistics_.l_preEmptiveRejected_,maxInitialPoints_);
			pruneTopScores(outputFrame.rightKP_,outputFrame.statistics_.r_preEmptiveRejected_,maxInitialPoints_);
		}
		else
		{
			pruneTopScores(outputFrame.leftKP_,maxInitialPoints_);
			pruneTopScores(outputFrame.rightKP_,maxInitialPoints_);
			
		}
	}
	
	if(internalRobustness_&StereoInternal::PREEMPTIVE_REJECTION)
	{
		//scan in the region around each point, and reject any 
		//points that geometrically have no clear match
		std::cout<<"still to implement"<<std::endl;
	}
	
	default_descriptor_->compute(LeftIn,outputFrame.leftKP_,outputFrame.leftDescrip_);
	default_descriptor_->compute(RightIn,outputFrame.rightKP_,outputFrame.rightDescrip_);
	
	getMatches(outputFrame);
	
	cv::drawMatches(limg,outputFrame.leftKP_,rimg,outputFrame.rightKP_,outputFrame.matches_,outimage);
	
		cv::namedWindow("a",cv::WINDOW_NORMAL);
//	cv::namedWindow("b",cv::WINDOW_NORMAL);
	
//	cv::drawKeypoints(limg,outputFrame.leftKP_,outimage);
//	cv::drawKeypoints(limg,outputFrame.leftKP_,outimage2);
	
	cv::imshow("a",outimage);
//	cv::imshow("b",outimage2);
	
	
	
	
	
	/*default_detector_->get
	
	settings_.detector_->getFeatures(image,output);
	if(settings_.internalOptions_&StereoInternal::ENFORCE_MAX_INITIAL_LIMIT)
	{
		getTopFeatures(output,settings_.maxInitialPoints_);
	}*/
	
//	cv::namedWindow("a",cv::WINDOW_NORMAL);
//	cv::imshow("a",limg);
	cv::waitKey(0);
	cv::destroyAllWindows();
	
}


void StereoRectifiedFeatures::pruneTopScores(std::vector< cv::KeyPoint >& output, int maxFeatures)
{
	if(output.size()>maxFeatures) //only remove if it is bigger than the maxfeatures
	{
		std::sort(output.begin(),output.end(),[](cv::KeyPoint a, cv::KeyPoint b) { return a.response > b.response; });
		output.erase(output.begin()+maxFeatures,output.end());
	}
}

void StereoRectifiedFeatures::pruneTopScores(std::vector< cv::KeyPoint >& output, std::vector< cv::KeyPoint >& rejected, int maxFeatures)
{
	if(output.size()>maxFeatures) //only remove if it is bigger than the maxfeatures
	{
		std::sort(output.begin(),output.end(),[](cv::KeyPoint a, cv::KeyPoint b) { return a.response > b.response; });
		rejected.insert(rejected.end(),output.begin()+maxFeatures,output.end());
		output.erase(output.begin()+maxFeatures,output.end());
	}
}

void StereoRectifiedFeatures::getMatches(StereoFrame& outputFrame)
{
	/*match them */
	switch(internalMatch_)
	{
		case StereoInternal::BRUTE_FORCE :
		{
			if(internalRobustness_&StereoInternal::CROSS_CHECK)
			{
				cv::BFMatcher matcher(getScoreMeasure(),true);
				matcher.match(outputFrame.leftDescrip_,outputFrame.rightDescrip_,outputFrame.matches_);
			}
			else
			{
				cv::BFMatcher matcher(getScoreMeasure(),false);
				matcher.match(outputFrame.leftDescrip_,outputFrame.rightDescrip_,outputFrame.matches_);
			}
			break;
		}
	}
}





	
	
}