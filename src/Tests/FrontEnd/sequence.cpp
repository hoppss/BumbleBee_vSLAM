
//#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

#include "FrontEnd/StereoFeatures/StereoRectifiedFeatures.hpp"
#include "FrontEnd/Window/SlidingWindow.hpp"
#include "Analysis/StereoRectifiedFeedback.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
		/*create internal matching + det+descr settings
	 */
	std::shared_ptr<DetSettings> brisk_det(new BRISKdet());
	brisk_det->setAdjustSettings(0.3,1);
	brisk_det->setInternalSettings(17,3,1.0);
	
	cv::Ptr<cv::DescriptorExtractor> brief_descr= cv::DescriptorExtractor::create("BRIEF");
	/*Configure front end
	 */
	
	StereoRectifiedFeatures bumbleBee;
	bumbleBee.default_descriptor_=brief_descr;
	bumbleBee.default_detector_=brisk_det;
	bumbleBee.maxInitialPoints_=500;
	
	bumbleBee.internalDescription_=StereoInternal::BRIEF_DESCR;
	
	bumbleBee.internalDetectionOptions_=StereoInternal::DetectionOptions::SIMPLE;
	
	bumbleBee.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::RobustnessCriteria::CROSS_CHECK);

	
	bumbleBee.internalMatch_=StereoInternal::MatchMethod::BRUTE_FORCE;
	
	bumbleBee.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(
																StereoInternal::KEEP_OUTLIER);
	
	bumbleBee.Initialize_("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");

	
	SlidingWindow mywindow_;
	mywindow_.internalDescription_=SlidingWindow::WindowDescription::BRIEF_DESCR;
	mywindow_.internalMatch_=SlidingWindow::WindowMatch::SIMPLE_WINDOW;
	mywindow_.lowe_ratio_=0.8;
	
	mywindow_.w_width_=3;
	
	
	
	/** get test images */
	cv::Mat limage,rimage;
	limage=cv::imread("/home/ubuntu/a1.ppm",cv::IMREAD_GRAYSCALE);
	rimage=cv::imread("/home/ubuntu/a2.ppm",cv::IMREAD_GRAYSCALE);
	
	cv::Mat limage2,rimage2;
	limage2=cv::imread("/home/ubuntu/r1.ppm",cv::IMREAD_GRAYSCALE);
	rimage2=cv::imread("/home/ubuntu/r2.ppm",cv::IMREAD_GRAYSCALE);
	
	
	StereoFrame myFrame,f2;
	bumbleBee.getFrame(myFrame,limage,rimage);
	

	mywindow_.pushFrame(myFrame);	
		
	bumbleBee.getFrame(f2,limage2,rimage2);

	mywindow_.pushFrame(f2);
	
	StereoRectifiedFeedback feed(bumbleBee.ptr_cal_);
	feed.printMatchScores(myFrame);
	feed.showInlier(limage,rimage,myFrame);
	feed.printMatchScores(f2);
	feed.showInlier(limage2,rimage2,f2);
	cv::destroyAllWindows();
	
	
	return 0;
}