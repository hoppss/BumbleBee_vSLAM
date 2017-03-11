#include "Manager/FWmanager.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
	FWmanager Man_;
	
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
	FrontEnd_config.maxInitialPoints_=400;
	
	FrontEnd_config.internalOptions_=StereoInternal::Options::ENFORCE_MAX_INITIAL_LIMIT;
	
	FrontEnd_config.internalMatch_=StereoInternal::BRUTE_FORCE;
	
	FrontEnd_config.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(0);
	
	FrontEnd_config.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::PREEMPTIVE_REJECTION | 
																										StereoInternal::CROSS_CHECK);

	
	Man_.FrontEnd_config=FrontEnd_config;

	Man_.singleDisplay();
	
	return 0;
}