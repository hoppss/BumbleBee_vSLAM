#ifndef STEREO_FRAME_HEADER_HPP
#define STEREO_FRAME_HEADER_HPP

#include <map>

#include "DataStructures/OutputData/StereoFrameStats.hpp"
#include "DataStructures/Transforms/Isometry.hpp"

namespace stereo{
	
enum KP_STATUS_
{
	NEW_KP,
	FURTHER_PROCESS,
	REJECTED,
	MATCH,
};
	
typedef unsigned int _KPKey_; //the type each unique map key is 
typedef unsigned int _FrameKey_;	
typedef uint64_t timestamp_;
typedef std::map<_KPKey_,int> frameFeatures; //ID,address index within the matches_vector
typedef std::map<_KPKey_,KP_STATUS_> windowMatch;
typedef std::map<_KPKey_,_KPKey_> windowReference;

class StereoFrame
{
	private:
		
	public:
		
		StereoFrame();
		frameFeatures outfeat_;
		/*out feature holds a mapping from KPKey to an address index within
		 *matches_, thus we can look up descriptors and KPS within each vector using
		 *only integer mappins. This means no copying is required, StereoFrame will hold
		 *all the information required for the existence of the program, and pass references to 
		 *external modules that wish to access features information*/ 
		_FrameKey_ ID_;
		_KPKey_ KP_total_;
		timestamp_ recordedTime_;
		windowReference previousMatches_;
		/*holds keys for each feature matched
		 * windowReference->first = keyID within this frame
		 * windowReference->Second =  keyID within the previous frame */
		std::vector<cv::KeyPoint> leftKP_,rightKP_;
		cv::Mat leftDescrip_,rightDescrip_;
		std::vector<cv::DMatch> matches_;
		Isometry previous_;
		windowMatch prev_match_;
		/*holds matching outputs towards the previously seen frame (only tracks one frame back)*/
		//TODO Timings
		
		cv::KeyPoint* getKeyPoint(_KPKey_ pointID,bool left);
		cv::Mat getDescriptor(_KPKey_ pointID,bool left);

};
}

#endif