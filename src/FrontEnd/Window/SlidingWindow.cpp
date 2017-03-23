#include "FrontEnd/Window/SlidingWindow.hpp"
#include <opencv2/core/core_c.h>
namespace stereo
{

SlidingWindow::SlidingWindow() : WindowInternal()
{
	features_added_=0;
}

	
void SlidingWindow::pushFrame(StereoFrame& latest)
{
 if(feat_per_frame_.size()>0)
 {
	 if(feat_per_frame_.size()+1>w_width_)
	 {
		 deleteFrame();
		 //delete the oldest frame if window size exceeds the widest width specified
	 }
	 
	 /*add the frame and calculate the information*/
	 AddFrame(latest);
	 
	 
 }
 else
 {
	 std::cout<<"Bootstrapping"<<std::endl;
	 //bootstrap the window
	 bootstrap(latest);
 }
}



void SlidingWindow::deleteFrame()
{
	//TODO save any info required by the stats object before deleting

	//delete motion
	
	//find all salient features with 
	
}


void SlidingWindow::AddFrame(StereoFrame& latest)
{
	/* match across frames, add to Salient feature vector if matches*/
	for(int index=0;index<latest.outKP_.size();index++)
	{
		if(internalMatch_&SIMPLE_WINDOW)
		{
			
		}
	//	if(!matchAcrossWindow(latest.outKP_.at(index)))
	//	{
			/*if no matching condition occured, add the keypoint as a fresh new salient feature*/
		//}
	}
	
}

void SlidingWindow::bootstrap(StereoFrame& first)
{
	/*setup initial configuration and load features */
	std::vector<unsigned int> temp_Ids;
	for(int index=0;index<first.outKP_.size();index++)
	{
		temp_Ids.push_back(features_added_);
		addNewKP(first.outKP_.at(index),0);
	}
	feat_per_frame_.push_front(temp_Ids);
}

void SlidingWindow::addNewKP(StereoKP KP,int frameNumber)
{
	features_[features_added_]=SalientFeature();
	features_[features_added_].correspondences_.push_back(KP);
	features_[features_added_].frameSeen_.push_back(frameNumber);

	features_added_++;

}

bool SlidingWindow::matchAcrossWindow(StereoKP KP)
{
//TODO add all the different configurations
	return bruteMatch(KP);

}

float SlidingWindow::singleDescMatch(cv::Mat& d1, cv::Mat& d2)
{
	if(internalDescription_&BRIEF_DESCR)
	{
		return cv::norm(d1,d2,cv::NORM_HAMMING);//check this
	}
	//todo
	else
	{
		return 1000.0;
	}
}

bool SlidingWindow::bruteMatch(StereoKP& KP)
{
	/*only returns the best matching score against all features in the dataset*/
	std::map<unsigned int,SalientFeature>::iterator it,found_it;
	it=features_.begin();
	found_it=it;
	float bestScore;
	
	
	
	for(;it!=features_.end();++it)
	{
		std::vector<StereoKP>::iterator sal_it;
		/*match against all SalientFeature descriptors (only left)*/
		
		sal_it=it->second.correspondences_.begin();
		std::cout<<getSalientBestScore(KP,it)<<std::endl;;
	}
}


float SlidingWindow::getSalientBestScore(StereoKP& KP, std::map< unsigned int, SalientFeature >::iterator& it_)
{
	float best;
	std::vector<StereoKP>::iterator sal_it;//iterate through salient feature set of descriptors
	sal_it=it_->second.correspondences_.begin();
	best=singleDescMatch(sal_it->leftDescr,KP.leftDescr);
	sal_it++;
	for(;sal_it!=it_->second.correspondences_.end();++sal_it)
	{
		float current=singleDescMatch(sal_it->leftDescr,KP.leftDescr);
		if(current<best)
		{
			best=current;
		}
	}
}











	
}

