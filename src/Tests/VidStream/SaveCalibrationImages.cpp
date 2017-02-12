#include "VidStream/FireWire.hpp"
#include <time.h>
int main(int argc,char** argv)
{
	stereo::FireWire bumbleBee;
	cv::Mat image;
	cv::Mat left,right;
	std::string overall_directory,left_prefix,right_prefix;
	
	
	
	
	if((argc<4)||(argc>4))
	{
		std::cout<<"incorrect number of parameters\n";
		std::cout<<"arg 1 =  overall_directory\n";
		std::cout<<"arg 2 = left prefix\n";
		std::cout<<"arg 3 =  right prefix\n";
		return 1;
	}
	
	overall_directory=std::string(argv[1]);
	left_prefix=std::string(argv[2]);
	right_prefix=std::string(argv[3]);
	
	
	time_t sec=time(0);
	bumbleBee.singleCapture(left,right);
	std::stringstream l,r;
	l<<overall_directory<<"/left/"<<left_prefix<<"_"<<sec<<".ppm";
	r<<overall_directory<<"/right/"<<right_prefix<<"_"<<sec<<".ppm";
	
	std::cout<<l.str()<<std::endl;
	std::cout<<r.str();
	
	cv::imwrite(l.str(),left);
	cv::imwrite(r.str(),right);

	return 0;
}