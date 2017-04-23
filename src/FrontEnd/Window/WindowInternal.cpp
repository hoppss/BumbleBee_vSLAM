

#include "FrontEnd/Window/WindowInternal.hpp"

namespace stereo
{

WindowInternal::WindowInternal(int size_)
{
	w_width_=size_;
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