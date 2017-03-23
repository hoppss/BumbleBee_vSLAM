#ifndef SLIDING_WINDOW_HEADER_HPP
#define SLIDING_WINDOW_HEADER_HPP

#include "FrontEnd/Window/WindowInternal.hpp"
#include "DataStructures/OutputData/SalientFeature.hpp"
#include <map>
#include <deque>

namespace stereo
{

class SlidingWindow : public WindowInternal
{
	private:
		void bootstrap(StereoFrame &first);
		unsigned int features_added_;
		std::map<unsigned int,SalientFeature> features_;
		std::deque<std::vector<unsigned int> > feat_per_frame_;
		std::deque<Isometry> motion_;
		bool matchAcrossWindow(StereoKP KP);
		void AddFrame(StereoFrame &latest);
		void deleteFrame();//remove oldest
		void addNewKP(StereoKP KP,int frameNumber);//always adds kp as new unique feature
		float singleDescMatch(cv::Mat &d1,cv::Mat &d2);
		float getSalientBestScore(StereoKP &KP,std::map<unsigned int,SalientFeature>::iterator &it_);
		bool bruteMatch(StereoKP &KP);
	public:
		SlidingWindow();
		void pushFrame(StereoFrame &latest);
		//motion estimate between two frames
		//
		//optimization
};
	
}

#endif