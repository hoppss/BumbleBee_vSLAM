
#include <DataStructures/DataSet/BumbleDataSet.hpp>
#include <DataStructures/OutputData/ImageDetections.hpp>
#include <FrontEnd/Detection/BRISKdet.hpp>

#include <iostream>

int main(int argc, char * argv[])
{
	using namespace stereo;

	
	std::shared_ptr<DetSettings> brisk_det(new BRISKdet);
	cv::FileStorage outFile("aa.xml",cv::FileStorage::WRITE);
	
	BumbleDataSet a("/home/ryan/DataSets/Mine/Decent-cloudy/recording-20170702-122129-924");
	bool end=false;
	cv::namedWindow( "l", cv::WINDOW_NORMAL );
	ImageDetections out;
	while(!end)
	{
	cv::Mat M=cv::Mat::eye(3,3,CV_64FC1);
	
	//brisk_det->getFeatures(a.getCurrentLeft(),out.detectedKP_);
	std::cout<<brisk_det->getStringName()<<std::endl;
	cv::imshow("l",a.getCurrentLeft());
	//cv::drawKeypoints(a.getCurrentLeft(),out.detectedKP_,ss);
	
	//cv::imshow("l2",ss);
	
	outFile<<"aa"<<out;
	//outFile<<"bitch"<<M;
	cv::waitKey(1000/15);
	end!=a.incrementFrame();
	}
	cv::destroyWindow("l");
	outFile.release();
	return 0;
}
