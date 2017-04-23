
//#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

#include "FrontEnd/StereoFeatures/StereoRectifiedFeatures.hpp"
#include "Analysis/StereoRectifiedFeedback.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
		/*create internal matching + det+descr settings
	 */
	std::shared_ptr<DetSettings> brisk_det(new BRISKdet());
	brisk_det->setAdjustSettings(0.05,1);
	brisk_det->setInternalSettings(2,3,1.0);
	
	cv::Ptr<cv::DescriptorExtractor> brief_descr= cv::DescriptorExtractor::create("BRIEF");
	/*Configure front end
	 */
	
	StereoRectifiedFeatures bumbleBee;
	bumbleBee.default_descriptor_=brief_descr;
	bumbleBee.default_detector_=brisk_det;
	bumbleBee.maxInitialPoints_=800;
	
	bumbleBee.internalDescription_=StereoInternal::BRIEF_DESCR;
	
	bumbleBee.internalDetectionOptions_=StereoInternal::DetectionOptions::SIMPLE;
	
	bumbleBee.internalRobustness_=static_cast<StereoInternal::RobustnessCriteria>(StereoInternal::RobustnessCriteria::POST_REJECTION|
																																								StereoInternal::RobustnessCriteria::PRUNE_INITIAL_SCORE);
	
	bumbleBee.internalMatch_=StereoInternal::MatchMethod::BRUTE_FORCE;
	
	bumbleBee.internalStatistics_=static_cast<StereoInternal::ComputeStatistics>(
																StereoInternal::KEEP_OUTLIER);
	
	bumbleBee.Initialize_("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml");

	
	/** get test images */
	cv::Mat limage,rimage;
	limage=cv::imread("/home/ubuntu/l1.ppm",cv::IMREAD_GRAYSCALE);
	rimage=cv::imread("/home/ubuntu/r1.ppm",cv::IMREAD_GRAYSCALE);

	bool stop=false;
	
			cv::namedWindow("left",cv::WINDOW_NORMAL);
		cv::namedWindow("rectl",cv::WINDOW_NORMAL);
		cv::namedWindow("match",cv::WINDOW_NORMAL);
		cv::namedWindow("inlier",cv::WINDOW_NORMAL);
		cv::namedWindow("outlier",cv::WINDOW_NORMAL);
		
	
	while(!stop)
	{
		StereoFrame myFrame;
		StereoFrameStats frameStat;
		
		std::unique_ptr<StereoFrame> ptr_(new StereoFrame);
		frameStat.setAllOn();
		bumbleBee.getFrame((*ptr_),limage,rimage,frameStat);
		stop=!bumbleBee.default_detector_->increment();

		
		
		StereoRectifiedFeedback feed(bumbleBee.ptr_cal_);
		
		cv::Mat origl,origr,rer,inlier,out;
		cv::Mat rel,matc;
		
		feed.getOriginalDetected(frameStat,origl,origr);
		feed.getRectDetected(myFrame,frameStat,rel,rer);
		feed.getRectifiedMatches(frameStat,(*ptr_),matc);
		
		feed.getSideSideRect(limage,rimage,inlier);
		feed.getSideSideRect(limage,rimage,out);
		cv::cvtColor(inlier,inlier,cv::COLOR_GRAY2RGB);
		cv::cvtColor(out,out,cv::COLOR_GRAY2RGB);
		
		
		
		feed.drawInlierMatches(inlier,(*ptr_),cv::Scalar(255,0,0));
		feed.drawEpiRejections(out,frameStat,cv::Scalar(0,0,255));

		cv::namedWindow("left",cv::WINDOW_NORMAL);
		cv::namedWindow("rectl",cv::WINDOW_NORMAL);
		cv::namedWindow("match",cv::WINDOW_NORMAL);
		cv::namedWindow("inlier",cv::WINDOW_NORMAL);
		cv::namedWindow("outlier",cv::WINDOW_NORMAL);
		
		
		cv::imshow("left",origl);
		cv::imshow("inlier",inlier);
		cv::imshow("rectl",rel);
		cv::imshow("match",matc);
		cv::imshow("outlier",out);
		cv::waitKey(0);
		
	}
		cv::destroyAllWindows();

	return 0;
}