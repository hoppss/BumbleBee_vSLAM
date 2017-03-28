#include "DataStructures/OutputData/StereoFrame.hpp"

namespace stereo
{
	
	
StereoFrame::StereoFrame()
{
	ID_=0;
	KP_total_=0;
}

cv::KeyPoint* StereoFrame::getKeyPoint(_KPKey_ pointID, bool left)
{
	
/*		StereoKP Ans;
	Ans.matchScore=output.matches_.at(Matchindex).distance;	
	Ans.left=output.leftKP_.at(output.matches_.at(Matchindex).queryIdx);
	Ans.right=output.rightKP_.at(output.matches_.at(Matchindex).trainIdx);
	output.leftDescrip_.row(Matchindex).copyTo(Ans.leftDescr);
	output.rightDescrip_.row(Matchindex).copyTo(Ans.rightDescr);
	*/
	
	int match_index;
	int kp_index;
	match_index=outfeat_.at(pointID);//gives an index in matches_ according to outfeat mapping
	if(left)
	{
		kp_index=matches_.at(match_index).queryIdx;//gets index given by DMATCH
		return &(leftKP_.at(kp_index));//returns a pointer to the KP structure
	}
	else
	{
		kp_index=matches_.at(match_index).trainIdx;
		return &(rightKP_.at(kp_index));
	}
	
	/*returns a pointer to a keypoint given the ID associated with outfeat_ map
	 * thus the pointer is working directly with leftKP_ vector elements which is
	 * assumed to never change throughout the lifetime of the stereoFrame,
	 note there is no error checking on this call. Entirely responsible on the 
	 other module to ensure the KP does indeed exist within this frame*/
}


cv::Mat StereoFrame::getDescriptor(_KPKey_ pointID, bool left)
{
	int match_index;
	int kp_index;
	match_index=outfeat_.at(pointID);//gives an index in matches_ according to outfeat mapping
	if(left)
	{
		kp_index=matches_.at(match_index).queryIdx;//gets index given by DMATCH
		return leftDescrip_.row(kp_index);
	}
	else
	{
		kp_index=matches_.at(match_index).trainIdx;//gets index given by DMATCH
		return rightDescrip_.row(kp_index);
	}
}








}