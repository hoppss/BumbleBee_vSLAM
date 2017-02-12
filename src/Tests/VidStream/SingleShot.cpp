
#include "VidStream/FireWire.hpp"

int main(int argc,char** argv)
{
	stereo::FireWire bumbleBee;
	cv::Mat image;
	cv::Mat left,right;
	
	for(int index=0;index<15;index++)
	{
		std::stringstream a,b,c;
		a<<"file_"<<index<<".ppm";
		b<<"file_left_"<<index<<".ppm";
		c<<"file_right_"<<index<<".ppm";
		bumbleBee.singleCapture(image);
		bumbleBee.singleCapture(left,right);
		cv::imwrite(a.str(),image);
		cv::imwrite(b.str(),left);
		cv::imwrite(c.str(),right);
	}
	return 0;
}