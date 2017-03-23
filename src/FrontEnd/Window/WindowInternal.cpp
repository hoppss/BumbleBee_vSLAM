

#include "FrontEnd/Window/WindowInternal.hpp"

namespace stereo
{

WindowInternal::WindowInternal()
{
	w_width_=1;
}

int WindowInternal::getScoreMeasure()
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

	
	
}