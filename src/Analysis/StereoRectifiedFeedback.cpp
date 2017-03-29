#include "Analysis/StereoRectifiedFeedback.hpp"

namespace stereo
{
	
StereoRectifiedFeedback::StereoRectifiedFeedback()
{

}


StereoRectifiedFeedback::StereoRectifiedFeedback(StereoRect* ptr)
{
	feed_cal=ptr;//NOTE there is no deep copying here, assumes the object stereoRect still exists in memory
}

/*get functions
 * 
 * 
 * 
 * */
void StereoRectifiedFeedback::getSingleRect(cv::Mat in, cv::Mat& out, bool left)
{
	/*rectifies a single image in, and stores it to the out image container.
	 * if left is true, assumes left image mapping, else assumes right image mapping */
	if(left)
	{
		out=cv::Mat(feed_cal->L_fMapx_.size(),in.type());
		cv::remap(in,out,feed_cal->L_fMapx_,feed_cal->L_fMapy_,cv::INTER_LINEAR);
	}
	else
	{
		out=cv::Mat(feed_cal->R_fMapx_.size(),in.type());
		cv::remap(in,out,feed_cal->R_fMapx_,feed_cal->R_fMapy_,cv::INTER_LINEAR);
	}
}




void StereoRectifiedFeedback::getSideSideRect(cv::Mat limg, cv::Mat rimg, cv::Mat& out)
{
	/*rectifies a left and right image, and returns the two side by side*/
	cv::Mat lRectified,rRectified;
	lRectified=cv::Mat(feed_cal->L_fMapx_.size(),limg.type()); //assuming grayscale
	rRectified=cv::Mat(feed_cal->R_fMapx_.size(),rimg.type());
	
	cv::remap(limg,lRectified,feed_cal->L_fMapx_,feed_cal->L_fMapy_,cv::INTER_LINEAR);
	cv::remap(rimg,rRectified,feed_cal->R_fMapx_,feed_cal->R_fMapy_,cv::INTER_LINEAR);
	
	getSideBySide(lRectified,rRectified,out);
	
	
}

void StereoRectifiedFeedback::getSideBySide(cv::Mat left, cv::Mat right, cv::Mat& out)
{
	/*takes two images, and creates a new image with both images next to each other, assumes they are 
	 * the same size and type*/
	out=cv::Mat(cv::Size(left.size().width+right.size().width,left.size().height),left.type());
	cv::Mat lroi(out,cv::Rect(0,0,left.size().width,left.size().height));
	cv::Mat rroi(out,cv::Rect(left.size().width,0,right.size().width,right.size().height));
	
	left.copyTo(lroi);
	right.copyTo(rroi);
}


void StereoRectifiedFeedback::getOriginalDetected(StereoFrameStats& debug, cv::Mat& lout, cv::Mat& rout)
{
	/*draws keypoints according to the original detected points i.e with no modifications, as opencv
	 * originally described them within the region of interest image*/
	if(debug.settings_&StereoFrameStats::KEEP_ROI_IMG)
	{
		cv::drawKeypoints(debug.leftROI_img_,debug.initial_lkp_,lout,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::drawKeypoints(debug.rightROI_img_,debug.initial_rkp_,rout,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	}
	else
	{
			std::cerr<<"error :  (getOriginalDetected) -KEEP_ROI_IMG flag was not set, unable to display original settings"<<std::endl;
	}
}

void StereoRectifiedFeedback::getRectDetected(StereoFrame &output,StereoFrameStats& debug, cv::Mat& lout, cv::Mat& rout)
{
	/*drawys keypoints on the left and right Rectified images*/
	if(debug.settings_&StereoFrameStats::KEEP_RECTIFIED)
	{
		std::cout<<"output size : "<<output.leftKP_.size()<<"\tdebug size : "<<debug.initial_lkp_.size()<<std::endl;
		cv::drawKeypoints(debug.leftRect_,output.leftKP_,lout,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::drawKeypoints(debug.rightRect_,output.rightKP_,rout,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	}
	else
	{
			std::cerr<<" error :  (getRectDetected) - KEEP_RECTIFIED_IMG flag was not set, unable to display"<<std::endl;
	}
}

void StereoRectifiedFeedback::getRectifiedMatches(StereoFrameStats& debug, StereoFrame& out, cv::Mat& outImage)
{
	/*draws the matches according to opencv calculated points, draws onto the outimage which is assumed a 
	 * coloured side by side rectified image*/
	if(debug.settings_&StereoFrameStats::KEEP_RECTIFIED)
	{
		cv::drawMatches(debug.leftRect_,out.leftKP_,
										debug.rightRect_,out.rightKP_,
										out.matches_,outImage,
										cv::Scalar::all(-1),cv::Scalar::all(-1),
										std::vector<char>(),cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	}
	else
	{
			std::cerr<<" error :  (getRectifiedMatches) - KEEP_RECTIFIED_IMG flag was not set, unable to display"<<std::endl;
	}
}






/*Draw functions 
 * 
 * 
 * 
 * */


void StereoRectifiedFeedback::drawInlierMatches(cv::Mat& inputOutput, StereoFrame& out, cv::Scalar col)
{
		/*assumes inputOutput is already a colour image*/
	for(frameFeatures::iterator it=out.outfeat_.begin();it!=out.outfeat_.end();++it)
	{
		cv::Point2f lP,rP;
		/*get left point*/
		lP=(out.getKeyPoint(it->first,true))->pt;
		rP=(out.getKeyPoint(it->first,false))->pt;
		
		rP.x+=(int)inputOutput.size().width/2.0;
		
		cv::circle(inputOutput,lP,3,col);
		cv::circle(inputOutput,rP,3,col);
		cv::line(inputOutput,lP,rP,col,1);
	}
	
}

void StereoRectifiedFeedback::drawEpiRejections(cv::Mat& inputOutput, StereoFrameStats& debug, cv::Scalar col)
{
	for(int index=0;index<debug.epiOut_l.size();++index)
	{
		cv::Point2f lP,rP;
		lP=debug.epiOut_l.at(index).pt;
		rP=debug.epiOut_r.at(index).pt;
		
		rP.x+=(int)inputOutput.size().width/2.0;
		
		cv::circle(inputOutput,lP,3,col);
		cv::circle(inputOutput,rP,3,col);
		cv::line(inputOutput,lP,rP,col,1);
		
	}

}


void StereoRectifiedFeedback::drawEpiRejections(cv::Mat& inputOutput, StereoFrameStats& debug, cv::Scalar col, cv::Scalar colDist)
{
		for(int index=0;index<debug.epiOut_l.size();++index)
	{
		cv::Point2f lP,rP;
		lP=debug.epiOut_l.at(index).pt;
		rP=debug.epiOut_r.at(index).pt;
		
		rP.x+=(int)inputOutput.size().width/2.0;
		
		cv::circle(inputOutput,lP,3,col);
		cv::circle(inputOutput,rP,3,col);
		cv::line(inputOutput,lP,rP,col,1);
		
		cv::Point2f distance_;

		distance_=lP;
		distance_.y=rP.y;

		cv::line(inputOutput,lP,distance_,colDist,1);
	}

}





}