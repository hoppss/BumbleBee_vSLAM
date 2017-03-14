#include "Analysis/StereoDrawing.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
	std::string inputDir;
	inputDir="/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml";
	StereoDrawing dr(inputDir); 
	
	cv::Mat l=cv::imread("/home/ubuntu/ll.ppm",cv::IMREAD_GRAYSCALE);
	cv::Mat r=cv::imread("/home/ubuntu/rr.ppm",cv::IMREAD_GRAYSCALE);
	cv::Mat out;
	cv::Mat lr,rr;
	
	
	
	dr.drawStereoEpi(l,r,out,true);
	
	cv::namedWindow("epi",cv::WINDOW_NORMAL);
	cv::imshow("epi",out);
	cv::waitKey(0);
	cv::destroyAllWindows();
	
	//dr.stereoRectify(l,lrect,true,true);
	//cv::imwrite("/home/ubuntu/ll_rect11.ppm",lrect);
	//dr.drawROI(lrect,l22,false,true,true);
	//cv::imwrite("/home/ubuntu/ll_rect.ppm",l22);

	return 0;
}