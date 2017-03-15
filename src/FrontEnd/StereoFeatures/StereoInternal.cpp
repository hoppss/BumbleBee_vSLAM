#include "FrontEnd/StereoFeatures/StereoInternal.hpp"

namespace stereo
{

StereoInternal::StereoInternal()
{
	maxRadius_=10.0;
	initialized_=false;
	n_rows=1;
	n_cols=1;
	maxInitialPoints_=5000;
}

int StereoInternal::getScoreMeasure()
{
	int Ans;
	switch(internalDescription_)
	{
		case BRIEF_DESCR :
		{
			Ans=cv::NORM_HAMMING;
			break;
		}
	}
	return Ans;
}

/***
 * Error checking functions to establish if the settings have been initialized to anything
 * or set to 0*/

//TODO FIX match methods..can only have one, not all three

bool StereoInternal::validDescription()
{
	if((internalDescription_>(BRIEF_DESCR))||(internalDescription_<0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool StereoInternal::validMatchMethod()
{
	if((internalMatch_>(BRUTE_FORCE|RADIUS|KNN_MATCH))||(internalMatch_<0))
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool StereoInternal::validRobustnessCriteria()
{
	if((internalRobustness_>(PREEMPTIVE_REJECTION|CROSS_CHECK|POST_REJECTION|PRUNE_INITIAL_SCORE))||(internalRobustness_<0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool StereoInternal::validStats()
{
	if((internalStatistics_>(DETECTION_TIME|CELL_DETECTION_TIME|DESCRIPTION_TIME|CELL_DESCRIPTION_TIME|OVERALL_TIME|ADMIN_TIME|KEEP_OUTLIER))||(internalStatistics_<0))
	{
		return false;
	}
	else
	{
		return true;
	}
}





	
}