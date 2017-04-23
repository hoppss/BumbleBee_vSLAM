#ifndef SLIDING_WINDOW_HEADER_HPP
#define SLIDING_WINDOW_HEADER_HPP

#include "FrontEnd/Window/WindowInternal.hpp"
#include "DataStructures/OutputData/StereoFrame.hpp"
#include <sba.h>
#include <map>
#include <deque>
#include <memory>

namespace stereo
{

/*typedef unsigned int _Key_; //the type each unique map key is 
typedef unsigned int _FrameID_;
typedef std::map<_Key_,SalientFeature*> mapFeat;
typedef std::deque<std::vector<_Key_> > mapFrame;
typedef std::deque<Isometry> odometer;*/


typedef std::shared_ptr<StereoFrame> FramePtr;
typedef std::deque<FramePtr> FrameQueue;
	
class SlidingWindow : public WindowInternal
{
	private:
	/*	enum KP_State
		{
			NEW_KP,
			MATCH,
			REJECTED,
		};
		void bootstrap(StereoFrame &first);
		_FrameID_ current_frame_;
		_Key_ overall_feat_;
		mapFeat features_;
		mapFrame frames_;
		odometer motion_;
//		bool matchAcrossWindow(StereoKP KP);
		void simpleWindowMatching(StereoFrame& latest);
		void AddFrame(StereoFrame &latest);
		void deleteFrame();//remove oldest
		void addNewKP(StereoKP KP,int frameNumber);//always adds kp as new unique feature
		float singleDescMatch(cv::Mat &d1,cv::Mat &d2);
//		float getSalientBestScore(StereoKP &KP,std::map<unsigned int,SalientFeature>::iterator &it_);
//		bool bruteMatch(StereoKP &KP);
		std::vector<float>::iterator loweRejection(std::vector<float> &allScores);
		void findLowestTwo(std::vector< float >& allScores,
											 std::vector< float >::iterator &best,
											 std::vector<float>::iterator &second);*/
		FrameQueue window_;
	public:
		SlidingWindow(int size_);
		void pushNewFrame(FramePtr &latestFrame);

};
	
}

#endif