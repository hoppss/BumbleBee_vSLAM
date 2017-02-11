
#include "VidStream/FireWire.hpp"

int main(int argc,char** argv)
{
	stereo::FireWire bumbleBee;
	cv::Mat image;
	
	for(int index=0;index<15;index++)
	{
		std::stringstream a;
		a<<"file_"<<index<<".ppm";
		bumbleBee.singleCapture(image);
		cv::imwrite(a.str(),image);
	}
	return 0;
}