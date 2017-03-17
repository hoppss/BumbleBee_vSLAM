
//#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

#include "FrontEnd/StereoFeatures/StereoRectifiedFeatures.hpp"
#include "Analysis/StereoRectifiedFeedback.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
		/*create internal matching + det+descr settings
	 */
//	std::shared_ptr<DetSettings> brisk_det(new BRISKdet());
//	cv::Ptr<cv::DescriptorExtractor> brief_descr= cv::DescriptorExtractor::create("BRIEF");
	/*Configure front end
	 */
	
//	StereoRectifiedFeatures bumbleBee;
//	bumbleBee.default_descriptor_=brief_descr;
//	bumbleBee.default_detector_=brisk_det;
//	bumbleBee.maxInitialPoints_=1300;
	
//	bumbleBee.internalDescription_=StereoInternal::BRIEF_DESCR;
	
//	bumbleBee.internalDetectionOptions_=StereoInternal::DetectionOptions::SIMPLE;
	
//	bumbleBee.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::RobustnessCriteria::CROSS_CHECK|
//																StereoInternal::RobustnessCriteria::POST_REJECTION);
	
//	bumbleBee.internalMatch_=StereoInternal::MatchMethod::BRUTE_FORCE;
	
//	bumbleBee.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(
	//															StereoInternal::KEEP_OUTLIER);
	
//	bumbleBee.Initialize_("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");

	
	/** get test images */
	cv::Mat limage,rimage;
	limage=cv::imread("/home/ubuntu/ll.ppm",cv::IMREAD_GRAYSCALE);
	rimage=cv::imread("/home/ubuntu/rr.ppm",cv::IMREAD_GRAYSCALE);

	
	//StereoFrame myFrame;
	
	//bumbleBee.getFrame(myFrame,testImage,rimage);

	return 0;
}