
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
	FrontEnd_config.setCameraInfo("/media/ubunntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");
	
	FrontEnd_config.internalDescription_= StereoInternal::BRIEF_DESCR;
	FrontEnd_config.descriptor_=brief_descr;
	
	FrontEnd_config.detector_=brisk_det;
	FrontEnd_config.maxInitialPoints_=400;
	
	FrontEnd_config.internalOptions_=StereoInternal::Options::ENFORCE_MAX_INITIAL_LIMIT;
	
	FrontEnd_config.internalMatch_=StereoInternal::BRUTE_FORCE;
	
	FrontEnd_config.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(0);
	
	FrontEnd_config.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::PREEMPTIVE_REJECTION | 
																										StereoInternal::CROSS_CHECK);
	StereoFeatures bumbleBee;
	
	/** get test images */
	cv::Mat testImage,rimage;
	testImage=cv::imread("/home/ubuntu/l.jpg",cv::IMREAD_GRAYSCALE);
	rimage=cv::imread("/home/ubuntu/r.jpg",cv::IMREAD_GRAYSCALE);

	
	StereoFrame myFrame;
	
	bumbleBee.getFrame(myFrame,testImage,rimage,FrontEnd_config);
	
	std::cout<<myFrame.matches_.size();
	
	return 0;
}