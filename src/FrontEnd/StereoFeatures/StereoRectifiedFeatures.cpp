
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

void StereoRectifiedFeatures::getFrame(StereoFrame& outputFrame, cv::Mat LeftIn, cv::Mat RightIn, StereoFrameStats& debug)
{
	cv::Mat lRectified,rRectified;
	lRectified=cv::Mat(ptr_cal_->L_fMapx_.size(),LeftIn.type());
	rRectified=cv::Mat(ptr_cal_->R_fMapx_.size(),RightIn.type());
	
	cv::remap(LeftIn,lRectified,ptr_cal_->L_fMapx_,ptr_cal_->L_fMapy_,cv::INTER_LINEAR);
	cv::remap(RightIn,rRectified,ptr_cal_->R_fMapx_,ptr_cal_->R_fMapy_,cv::INTER_LINEAR);

	
	/*rectify the left and right images, includes black space and is the same size as the original image,
	 * with ROI already computed*/
	cv::Mat limg(lRectified,ptr_cal_->l_ROI_),rimg(rRectified,ptr_cal_->r_ROI_);//set ROI 
	
	if(debug.settings_&StereoFrameStats::KEEP_RECTIFIED)
	{
		lRectified.copyTo(debug.leftRect_);
		rRectified.copyTo(debug.rightRect_);
	}
	if(debug.settings_&StereoFrameStats::KEEP_ROI_IMG)
	{
		limg.copyTo(debug.leftROI_img_);
		rimg.copyTo(debug.rightROI_img_);
	}
	//dertect features in each region of interest according to the detecion method and settings
	//in this case, it uses default settings throughout the run (no adaptive no modifications from initial
	//setup)
	default_detector_->getFeatures(limg,outputFrame.leftKP_);
	default_detector_->getFeatures(rimg,outputFrame.rightKP_);
	
	
	
	//change to rectified coora
	for(int index=0;index<outputFrame.leftKP_.size();index++)
	{
		/*offset into*/
	}
	


	if(internalRobustness_&StereoInternal::PRUNE_INITIAL_SCORE)
	{
		//only keep the maxInitialPoints with the Highest detector scores
		if(debug.settings_&StereoFrameStats::KEEP_PRE_REJECTED)
		{
			pruneTopScores(outputFrame.leftKP_,debug.l_preEmptiveRejected_,maxInitialPoints_);
			pruneTopScores(outputFrame.rightKP_,debug.r_preEmptiveRejected_,maxInitialPoints_);
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
	
	default_descriptor_->compute(limg,outputFrame.leftKP_,outputFrame.leftDescrip_);
	default_descriptor_->compute(rimg,outputFrame.rightKP_,outputFrame.rightDescrip_);
	
	getMatches(outputFrame);
	
	/*robust rejection */
	if(internalRobustness_&StereoInternal::POST_REJECTION)
	{
		epiPoleReject(outputFrame,debug);
	}
	else
	{
		for(int index=0;index<outputFrame.matches_.size();index++)
		{
			outputFrame.outfeat_[outputFrame.KP_total_]=index;
			++outputFrame.KP_total_;
		}
	}
	
	/* Triangulation */
	
	/* estimate Covariance */
	
	/*estimate stats + plot images */

	
}


void StereoRectifiedFeatures::SimpleFrame(StereoFrame& outputFrame, cv::Mat LeftIn, cv::Mat RightIn)
{
	
//TODO
	
	
	
	/* Triangulation */
	
	/* estimate Covariance */
	
	/*estimate stats + plot images */

	
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

void StereoRectifiedFeatures::epiPoleReject(StereoFrame& outputFrame)
{
	for(int index=0;index<outputFrame.matches_.size();index++)
	{
		float rms=epiLineError(outputFrame.leftKP_.at(outputFrame.matches_.at(index).queryIdx).pt,
											 outputFrame.rightKP_.at(outputFrame.matches_.at(index).trainIdx).pt);
		if(rms<2*epiThresh_)
		{
			/*add new feature mapping as an inlier*/
			outputFrame.outfeat_[outputFrame.KP_total_]= index;
			++outputFrame.KP_total_;
		}
		
	}
}

void StereoRectifiedFeatures::epiPoleReject(StereoFrame& outputFrame, StereoFrameStats& debug)
{
	for(int index=0;index<outputFrame.matches_.size();index++)
	{
		float rms=epiLineError(outputFrame.leftKP_.at(outputFrame.matches_.at(index).queryIdx).pt,
											 outputFrame.rightKP_.at(outputFrame.matches_.at(index).trainIdx).pt);
		if(rms>2*epiThresh_)//note the opposite signs, 
		{
			/*OUTLIER */
			if(debug.settings_&StereoFrameStats::KEEP_OUTLIER)
			{
				debug.epiOut_l.push_back(outputFrame.leftKP_.at(outputFrame.matches_.at(index).queryIdx));
				debug.epiOut_l.push_back(outputFrame.rightKP_.at(outputFrame.matches_.at(index).trainIdx));
			}
		}
		else
		{
			outputFrame.outfeat_[outputFrame.KP_total_]= index;
			++outputFrame.KP_total_;
		}
		
	}
	

}

/*

StereoKP StereoRectifiedFeatures::buildStereoKP(StereoFrame& output, int Matchindex)
{
	StereoKP Ans;
	Ans.matchScore=output.matches_.at(Matchindex).distance;	
	Ans.left=output.leftKP_.at(output.matches_.at(Matchindex).queryIdx);
	Ans.right=output.rightKP_.at(output.matches_.at(Matchindex).trainIdx);
	output.leftDescrip_.row(Matchindex).copyTo(Ans.leftDescr);
	output.rightDescrip_.row(Matchindex).copyTo(Ans.rightDescr);
	
	return Ans;
}*/

float StereoRectifiedFeatures::epiLineError(cv::Point2f left, cv::Point2f right)
{
		/*correct for region of interest,
	 * The original rectified images are row aligned, not the region of interest 
	 * images which have different sizes*/
	//left.x+=ptr_cal_->l_ROI_.x;  X is irrelevant to the epi pole line calculation
	float leftY=left.y+ptr_cal_->l_ROI_.y;
	float rightY=right.y+ptr_cal_->r_ROI_.y;

	
	return 2*abs(leftY-rightY);//times two because we rae including both error as seen from the
	//left image, and the image as seen from the right image,
	//because they are rectified images, these errors are the same

}




}


	
	
