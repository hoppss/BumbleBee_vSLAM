#include "FrontEnd/Window/SlidingWindow.hpp"
#include <opencv2/core/core_c.h>
namespace stereo
{

SlidingWindow::SlidingWindow() : WindowInternal()
{
//	overall_feat_=0;
//	current_frame_=0;
}

	
// void SlidingWindow::pushFrame(StereoFrame& latest)
// {
 //if(frames_.size()>0)
 //{
	// if(frames_.size()+1>w_width_)
	 //{
// 		 deleteFrame();
		 //delete the oldest frame if window size exceeds the widest width specified
// 	 }
	 
	 /*add the frame and calculate the information*/
// 	 AddFrame(latest);
//  }
//  else
//  {
// 	 std::cout<<"Bootstrapping"<<std::endl;
	 //bootstrap the window
// 	 bootstrap(latest);
//  }
// }



// void SlidingWindow::deleteFrame()
// {
	//TODO save any info required by the stats object before deleting

	//delete motion
	
	//find all salient features with 
	
// }


// void SlidingWindow::AddFrame(StereoFrame& latest)
// {
// 	current_frame_++;
	/* match across frames, add to Salient feature vector if matches*/
// 	for(int index=0;index<latest.outKP_.size();index++)
// 	{
// 		if(internalMatch_&SIMPLE_WINDOW)
// 		{
// 			simpleWindowMatching(latest);
// 		}
	//	if(!matchAcrossWindow(latest.outKP_.at(index)))
	//	{
// 			/*if no matching condition occured, add the keypoint as a fresh new salient feature*/
		//}
// 	}
	
// }

// void SlidingWindow::simpleWindowMatching(StereoFrame& latest)
// {
// 	/*performs the most basic matching across frames,
// 	 gets the distance to every salient point mat*/
	
// 	/*for each stereoKP, compare it against all the Salient Features*/
// 	std::vector<StereoKP>::iterator kp_iterator;
	
// 	kp_iterator=latest.outKP_.begin();
	//for(;kp_iterator!=latest.outKP_.end();++kp_iterator)
// 	{
		//iterate through current stereo Keypoint
// 		std::vector<float> scores_;//match scores against all salient features
// 		std::vector<mapFeat::iterator> references_;//holds reference iterators for each salient feature
		//that does not already have a match 
		
// 		mapFeat::iterator salient_iterator;
// 		salient_iterator=features_.begin();
		
// 		for(;salient_iterator!=features_.end();++salient_iterator)
		//{
// 			//if salient features latest stereoKP was found in
			//the current frame,then dont add it to the list
// 			if(std::find(salient_iterator->second->frameSeen_.begin(),
			//						 salient_iterator->second->frameSeen_.end(),frames_.size())==salient_iterator->second->frameSeen_.end())
// 			{
				//frame ID was not found, ie it still does not have a match in the latest frame, get its score
// 				float score=singleDescMatch(kp_iterator->leftDescr,
// 																	(salient_iterator->second->correspondences_.back()).leftDescr);
// 				scores_.push_back(score);
		//		references_.push_back(salient_iterator);
/*			}
			else
			{
				//TODO find the best match and swop it in 
			}
		}
		
		
		if(scores_.size()<2)
		{
			//add it as a new kp
			//all the salient features already have matches
			addNewKP(*kp_iterator,current_frame_);
			
		}
		else
		{
			std::vector<float>::iterator foundIterator=loweRejection(scores_);
			if(foundIterator!=scores_.end())
			{*/
				/*a unique enough match has been found, update the feature info*/
// 			}
// 		}
// 	}
	
	
	
// }


// void SlidingWindow::bootstrap(StereoFrame& first)
// {
	/*setup initial configuration and load features */
// 	std::vector<unsigned int> temp_Ids;
// 	for(int index=0;index<first.outKP_.size();index++)
// 	{
// 		temp_Ids.push_back(overall_feat_);
// // 		addNewKP(first.outKP_.at(index),current_frame_);
// 	}
// 	frames_.push_front(temp_Ids);
// }
// 
// void SlidingWindow::addNewKP(StereoKP KP,int frameNumber)
// {
// 	features_[overall_feat_]=new SalientFeature();
// 	featdures_[overall_feat_]->correspondences_.push_back(KP);
// 	features_[overall_feat_]->frameSeen_.push_back(frameNumber);
// 
// 	overall_feat_++;
// 
// }



// float SlidingWindow::singleDescMatch(cv::Mat& d1, cv::Mat& d2)
// {
// 	if(internalDescription_&BRIEF_DESCR)
// 	{
// 		return cv::norm(d1,d2,cv::NORM_HAMMING);//check this
// 	}
	//todo
// 	else
// 	{
// 		return 1000.0;
// 	}
// }


//bool SlidingWindow::bruteMatch(StereoKP& KP)
//{
//	/*only returns the best matching score against all features in the dataset*/
//	std::map<unsigned int,SalientFeature>::iterator it,found_it;
//	it=features_.begin();
//	found_it=it;
//	float bestScore;
	
	
	
//	for(;it!=features_.end();++it)
//	{
//		std::vector<StereoKP>::iterator sal_it;
	//	/*match against all SalientFeature descriptors (only left)*/
		
//		sal_it=it->second.correspondences_.begin();
//		std::cout<<getSalientBestScore(KP,it)<<std::endl;;
//	}
//}


//float SlidingWindow::getSalientBestScore(StereoKP& KP, std::map< unsigned int, SalientFeature >::iterator& it_)
//{
//	float best;
//	std::vector<StereoKP>::iterator sal_it;//iterate through salient feature set of descriptors
//	sal_it=it_->second.correspondences_.begin();
//	best=singleDescMatch(sal_it->leftDescr,KP.leftDescr);
//	sal_it++;
//	for(;sal_it!=it_->second.correspondences_.end();++sal_it)
//	{
//		float current=singleDescMatch(sal_it->leftDescr,KP.leftDescr);
//		if(current<best)
//		{
///			best=current;
//		}
//	}
//}


// std::vector<float>::iterator SlidingWindow::loweRejection(std::vector< float >& allScores)
// {
	/*note: always assumes there are atleast more than two matching scores*/
	/*
	std::vector<float>::iterator lowest,secondlowest;
	findLowestTwo(allScores,lowest,secondlowest);
	// test 
	if((*lowest)<lowe_ratio_*(*secondlowest))
	{
		//unique match, return the iterator where it was found
		return lowest;
	}
	else
	{
		//TODO figure out what to do with it
		//compare and get the most suitable or discard it completely
		return allScores.end();//failed lowe rejection test ..non unique
		
	}

}

void SlidingWindow::findLowestTwo(std::vector< float >& allScores, std::vector< float >::iterator & best, std::vector< float >::iterator& second)
{*/
	/*assumes it is bigger than two elements in length*/
/*	float d1,d2;//best and second lowest matching scores
	
	//initialize to the first two floating numbers
	if(allScores.at(0)<allScores.at(1))
	{
		d1=allScores.at(0);
		best=allScores.begin();
		d2=allScores.at(1);
		second=allScores.begin();
		++second;
	}
	else
	{
		d1=allScores.at(1);
		best=allScores.begin();
		++best;
		d2=allScores.at(0);
		second=allScores.begin();
	}
	
	//find the two lowest matching scores
	
	for(std::vector<float>::iterator score_it=(allScores.begin()+2);score_it!=allScores.end();++score_it)
	{
		if(*score_it<d2)//if current score is better than the second best
		{
			if(*score_it<d1)
			{
				//current is better than both previous scores
				d2=d1;
				d1=*score_it;
				second=best;
				best=score_it;
			}
			else
			{
				//current is better than second lowest
				d2=*score_it;
				second=score_it;
			}
		}

	}
	

}


*/









	
}


