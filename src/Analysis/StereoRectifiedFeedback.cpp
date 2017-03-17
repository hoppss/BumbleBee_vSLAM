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

void StereoRectifiedFeedback::RectifyImg(cv::Mat limg, cv::Mat rimg, cv::Mat& out)
{
	cv::Mat lRectified,rRectified;
	lRectified=cv::Mat(feed_cal->L_fMapx_.size(),limg.type()); //assuming grayscale
	rRectified=cv::Mat(feed_cal->R_fMapx_.size(),rimg.type());
	
	cv::remap(limg,lRectified,feed_cal->L_fMapx_,feed_cal->L_fMapy_,cv::INTER_LINEAR);
	cv::remap(rimg,rRectified,feed_cal->R_fMapx_,feed_cal->R_fMapy_,cv::INTER_LINEAR);
	
	sideBySide(lRectified,rRectified,out);
	
	
}

void StereoRectifiedFeedback::sideBySide(cv::Mat left, cv::Mat right, cv::Mat& out)
{
	out=cv::Mat(cv::Size(left.size().width+right.size().width,left.size().height),left.type());
	cv::Mat lroi(out,cv::Rect(0,0,left.size().width,left.size().height));
	cv::Mat rroi(out,cv::Rect(left.size().width,0,right.size().width,right.size().height));
	
	left.copyTo(lroi);
	right.copyTo(rroi);
}


void StereoRectifiedFeedback::displayRectifiedMatches(cv::Mat lrect, cv::Mat rrect, StereoFrame out)
{
	std::vector<cv::KeyPoint> corrected_left,corrected_right;
	cv::namedWindow("rectifiedMatches",cv::WINDOW_NORMAL);
	cv::namedWindow("colour",cv::WINDOW_NORMAL);
	cv::Mat outimage,colour;
	sideBySide(lrect,rrect,outimage);
	cv::cvtColor(outimage,colour,cv::COLOR_GRAY2RGB);
	for(int index=0;index<out.leftKP_.size();index++)
	{
		cv::KeyPoint temp=out.leftKP_.at(index);
		temp.pt.x+=feed_cal->l_ROI_.x;
		temp.pt.y+=feed_cal->l_ROI_.y;
		corrected_left.push_back(temp);
	}
	
		for(int index=0;index<out.rightKP_.size();index++)
	{
		cv::KeyPoint temp=out.rightKP_.at(index);
		temp.pt.x+=feed_cal->r_ROI_.x;
		temp.pt.y+=feed_cal->r_ROI_.y;
		corrected_right.push_back(temp);
	}
	
	cv::drawMatches(lrect,corrected_left,rrect,corrected_right,out.matches_,outimage);

	cv::imshow("rectifiedMatches",outimage);
	cv::waitKey(0);
	cv::destroyWindow("rectifiedMatches");
	cv::destroyWindow("colour");
	
}

void StereoRectifiedFeedback::RectifyImg(cv::Mat in, cv::Mat& out, bool left)
{
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

void StereoRectifiedFeedback::drawStereoKP(StereoKP in, cv::Mat &inputOutput, cv::Scalar col)
{
	/* draws a match onto an existing sideBySide image*/
	cv::Point2f lcorrect,rcorrect;
	
	lcorrect=in.left.pt;
	lcorrect.x+=feed_cal->l_ROI_.x;
	lcorrect.y+=feed_cal->l_ROI_.y;
	
	/* also includes the shift to the right image when viewed side by side*/
	rcorrect=in.right.pt;
	rcorrect.x+=feed_cal->r_ROI_.x+(int)inputOutput.size().width/2.0;
	rcorrect.y+=feed_cal->r_ROI_.y;
	
	cv::circle(inputOutput,lcorrect,3,col);
	cv::circle(inputOutput,rcorrect,3,col);
	cv::line(inputOutput,lcorrect,rcorrect,col,1);
}

void StereoRectifiedFeedback::drawStereoKP(StereoKP in, cv::Mat& inputOutput, cv::Scalar col, cv::Scalar col2)
{
		/* draws a match onto an existing sideBySide image*/
	cv::Point2f lcorrect,rcorrect;
	
	lcorrect=in.left.pt;
	lcorrect.x+=feed_cal->l_ROI_.x;
	lcorrect.y+=feed_cal->l_ROI_.y;
	
	/* also includes the shift to the right image when viewed side by side*/
	rcorrect=in.right.pt;
	rcorrect.x+=feed_cal->r_ROI_.x+(int)inputOutput.size().width/2.0;
	rcorrect.y+=feed_cal->r_ROI_.y;
	
	cv::circle(inputOutput,lcorrect,3,col);
	cv::circle(inputOutput,rcorrect,3,col);
	cv::line(inputOutput,lcorrect,rcorrect,col,1);
	/* also draws the distance to the epi polar line for each Left point*/
	cv::Point2f epiPoint;
	epiPoint=rcorrect;
	epiPoint.x=lcorrect.x;
	
	cv::line(inputOutput,lcorrect,epiPoint,col2,2);
	
//	epiPoint=lcorrect;
//	epiPoint.x=rcorrect.x;
	
//	cv::line(inputOutput,rcorrect,epiPoint,col2,2);
	
}


void StereoRectifiedFeedback::showInlierOutlier(cv::Mat lIn,cv::Mat rIn,StereoFrame out)
{
	cv::Mat lRect,rRect,combined;
	RectifyImg(lIn,rIn,combined);
	
	cv::cvtColor(combined,combined,cv::COLOR_GRAY2RGB);
	drawInliers(combined,out,cv::Scalar(0,255,0),cv::Scalar(255,0,0));
	drawOutliers(combined,out,cv::Scalar(0,0,255),cv::Scalar(255,0,255));
	drawEpiLines(combined,10);

	cv::namedWindow("InOut",cv::WINDOW_NORMAL);
	cv::imshow("InOut",combined);
	cv::waitKey(0);
	cv::destroyWindow("InOut");
}

void StereoRectifiedFeedback::showInlier(cv::Mat lIn, cv::Mat rIn, StereoFrame out)
{
	cv::Mat lRect,rRect,combined;
	RectifyImg(lIn,rIn,combined);
	
	cv::cvtColor(combined,combined,cv::COLOR_GRAY2RGB);
	drawInliers(combined,out,cv::Scalar(0,255,0),cv::Scalar(255,0,0));
	std::cout<<"totalPoints "<<out.matches_.size()<<"\tinlierRatio "<<(out.outKP_.size()/((float)out.matches_.size()))<<std::endl;
	cv::namedWindow("InOut",cv::WINDOW_NORMAL);
	cv::imshow("InOut",combined);
	cv::waitKey(0);
	cv::destroyWindow("InOut");
}



void StereoRectifiedFeedback::drawInliers(cv::Mat& inputOutput, StereoFrame& out, cv::Scalar col)
{
	for(int index=0;index<out.outKP_.size();index++)
	{
		drawStereoKP(out.outKP_.at(index),inputOutput,col);
	}
}

void StereoRectifiedFeedback::drawInliers(cv::Mat& inputOutput, StereoFrame& out, cv::Scalar col, cv::Scalar col2)
{
	for(int index=0;index<out.outKP_.size();index++)
	{
		drawStereoKP(out.outKP_.at(index),inputOutput,col,col2);
	}
}



void StereoRectifiedFeedback::drawOutliers(cv::Mat& inputOutput, StereoFrame& out, cv::Scalar col)
{
	for(int index=0;index<out.statistics_.outliers_.size();index++)
	{
		drawStereoKP(out.statistics_.outliers_.at(index),inputOutput,col);
	}

}

void StereoRectifiedFeedback::drawOutliers(cv::Mat& inputOutput, StereoFrame& out, cv::Scalar col, cv::Scalar col2)
{
		for(int index=0;index<out.statistics_.outliers_.size();index++)
	{
		drawStereoKP(out.statistics_.outliers_.at(index),inputOutput,col,col2);
	}
}

void StereoRectifiedFeedback::drawEpiLines(cv::Mat& inputOutput, int total)
{
	for(int index=0;index<total;index++)
	{
		int step=inputOutput.size().height/(total);
		cv::Point2f leftP(0,index*step);
		cv::Point2f rightP(inputOutput.size().width-1,index*step);
		cv::line(inputOutput,leftP,rightP,cv::Scalar(255,255,0),1);
	}
}




}