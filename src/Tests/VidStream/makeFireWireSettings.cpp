#include "VidStream/PointGrey.hpp"
#include <opencv2/highgui.hpp>

int main(int argc, char *argv[])
{
	stereo::PointGrey bumbleBee;
	
	bumbleBee.dcinit();
	bumbleBee.updateSettings();
	cv::Mat l,r;
	cv::namedWindow("a",cv::WINDOW_NORMAL);
	if(bumbleBee.openStream())
	{
		uint64_t previous,current;
		float rate;
		previous=0;
		while(true)
		{
		bumbleBee.getLatestFrame(l,r,current);	
		rate=(current-previous)/1000.0;
		previous=current;
		cv::waitKey(1);
		std::cout<<rate<<std::endl;
		cv::imshow("a",l);
		}
		bumbleBee.closeStream();
	}
	cv::destroyAllWindows();
	
	
   return 0;
}