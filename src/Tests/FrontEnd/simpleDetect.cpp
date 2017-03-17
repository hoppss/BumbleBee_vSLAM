
//#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

#include "FrontEnd/StereoFeatures/StereoRectifiedFeatures.hpp"
#include "Analysis/StereoRectifiedFeedback.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
		/*create internal matching + det+descr settings
	 */
	std::shared_ptr<DetSettings> brisk_det(new BRISKdet());
	brisk_det->setAdjustSettings(0.3,1);
	brisk_det->setInternalSettings(1,3,1.0);
	
	cv::Ptr<cv::DescriptorExtractor> brief_descr= cv::DescriptorExtractor::create("BRIEF");
	/*Configure front end
	 */
	
	StereoRectifiedFeatures bumbleBee;
	bumbleBee.default_descriptor_=brief_descr;
	bumbleBee.default_detector_=brisk_det;
	bumbleBee.maxInitialPoints_=1300;
	
	bumbleBee.internalDescription_=StereoInternal::BRIEF_DESCR;
	
	bumbleBee.internalDetectionOptions_=StereoInternal::DetectionOptions::SIMPLE;
	
	bumbleBee.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::RobustnessCriteria::CROSS_CHECK);
	
	bumbleBee.internalMatch_=StereoInternal::MatchMethod::BRUTE_FORCE;
	
	bumbleBee.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(
																StereoInternal::KEEP_OUTLIER);
	
	bumbleBee.Initialize_("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");

	
	/** get test images */
	cv::Mat testImage,rimage;
	testImage=cv::imread("/home/ubuntu/ll.ppm",cv::IMREAD_GRAYSCALE);
	rimage=cv::imread("/home/ubuntu/rr.ppm",cv::IMREAD_GRAYSCALE);

	bool stop=false;
	while(!stop)
	{
		StereoFrame myFrame;
		bumbleBee.getFrame(myFrame,testImage,rimage);
		stop=!bumbleBee.default_detector_->increment();

		
		
		StereoRectifiedFeedback feed(bumbleBee.ptr_cal_);
		feed.showInlier(testImage,rimage,myFrame);
		cv::destroyAllWindows();
	}
	return 0;
}