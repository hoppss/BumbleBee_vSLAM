
#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"


int main(int argc, char * argv[])
{
	using namespace stereo;
		/*create internal matching + det+descr settings
	 */
	std::shared_ptr<DetSettings> brisk_det(new BRISKdet());
	cv::Ptr<cv::DescriptorExtractor> brief_descr= cv::DescriptorExtractor::create("BRIEF");
	/*Configure front end
	 */
	StereoInternal FrontEnd_config;
	FrontEnd_config.setCameraInfo("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");
	
	FrontEnd_config.internalDescription_= StereoInternal::BRIEF_DESCR;
	FrontEnd_config.descriptor_=brief_descr;
	
	FrontEnd_config.detector_=brisk_det;
	
	FrontEnd_config.internalOptions_=static_cast<StereoInternal::Options>(0);
	
	FrontEnd_config.internalMatch_=StereoInternal::BRUTE_FORCE;
	
	FrontEnd_config.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(0);
	
	FrontEnd_config.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::PREEMPTIVE_REJECTION | 
																										StereoInternal::CROSS_CHECK);
	std::cout<<static_cast<int>(FrontEnd_config.internalRobustness_)<<std::endl;
	StereoFeatures bumbleBee;
	
	/** get test images */
	cv::Mat testImage;
	testImage=cv::imread("/home/ubuntu/l.jpg",cv::IMREAD_GRAYSCALE);
	
	std::vector<cv::KeyPoint> mytest;
	
	bumbleBee.GetFeatures(testImage,mytest,FrontEnd_config);
	
	std::cout<<"kp : "<<mytest.size()<<std::endl;
	return 0;
}