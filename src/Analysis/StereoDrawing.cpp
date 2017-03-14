#include "Analysis/StereoDrawing.hpp"



namespace stereo {

StereoDrawing::StereoDrawing(Stereo con)
{
	config_=con;
}

StereoDrawing::StereoDrawing()
{

}

StereoDrawing::StereoDrawing(std::string dir)
{
	cv::FileStorage fs("/media/ubuntu/SD_CARD/ConfigurationFiles/BumbleBeeConfig.xml",cv::FileStorage::READ);
	
	if(fs.isOpened())
	{	
		fs["stereocalibration"]>>config_;
		fs.release();
	}
	else
	{
		std::cout<<"Could not open file specefied at "<<dir<<std::endl;
	}
}


void StereoDrawing::drawEpiLine()
{

}

void StereoDrawing::stereoRectify(cv::Mat input, cv::Mat& output,bool leftImage, bool includeDistortion)
{
	//TODO error checking
	if(leftImage)
	{
		if(includeDistortion)
		{
			output=cv::Mat(config_.cam_left_.rect_mapx_dist_.size(),input.type());
			
			
			/*full rectification*/
			cv::remap(input,output,
								config_.cam_left_.rect_mapx_dist_,config_.cam_left_.rect_mapy_dist_,
								cv::INTER_LINEAR,cv::BORDER_TRANSPARENT);

			
		}
		else
		{
			output=cv::Mat(config_.cam_left_.rect_mapx_.size(),input.type());
			/*rectification post undistortion*/
			
				cv::remap(input,output,
								config_.cam_left_.rect_mapx_,config_.cam_left_.rect_mapy_,
								cv::INTER_LINEAR,cv::BORDER_TRANSPARENT);
		}
	}
	else
	{
		if(includeDistortion)
		{
			output=cv::Mat(config_.cam_right_.rect_mapx_dist_.size(),input.type());
			
			
			/*full rectification*/
			cv::remap(input,output,
								config_.cam_right_.rect_mapx_dist_,config_.cam_right_.rect_mapy_dist_,
								cv::INTER_LINEAR,cv::BORDER_TRANSPARENT);

			
		}
		else
		{
			output=cv::Mat(config_.cam_right_.rect_mapx_.size(),input.type());
			/*rectification post undistortion*/
			
				cv::remap(input,output,
								config_.cam_right_.rect_mapx_,config_.cam_right_.rect_mapy_,
								cv::INTER_LINEAR,cv::BORDER_TRANSPARENT);
		}
		
	}
}


void StereoDrawing::drawROI(cv::Mat input, bool left, bool includeDistortion)
{
	cv::Mat output;
	cv::cvtColor(input,output,cv::COLOR_GRAY2BGR);
	
	if(left)
	{
		if(includeDistortion)
		{
			cv::rectangle(output,config_.cam_left_.ROI_wD_,cv::Scalar(0,0,255));
		}
		else
		{
			cv::rectangle(output,config_.cam_left_.ROI_,cv::Scalar(0,0,255));
		}
	}
	else
	{
		if(includeDistortion)
		{
			cv::rectangle(output,config_.cam_right_.ROI_wD_,cv::Scalar(255,0,255));
		}
		else
		{
			cv::rectangle(output,config_.cam_right_.ROI_,cv::Scalar(255,0,255));
		}
	}

	cv::namedWindow("ROI_Interest",cv::WINDOW_NORMAL);
	cv::imshow("ROI_Interest",output);
	cv::waitKey(0);
	cv::destroyWindow("ROI_Interest");
	
}


void StereoDrawing::drawROI(cv::Mat input, cv::Mat& output, bool display, bool left, bool includeDistortion)
{
	cv::cvtColor(input,output,cv::COLOR_GRAY2BGR);
	
	if(left)
	{
		if(includeDistortion)
		{
			cv::rectangle(output,config_.cam_left_.ROI_wD_,cv::Scalar(0,0,255));
		}
		else
		{
			cv::rectangle(output,config_.cam_left_.ROI_,cv::Scalar(0,0,255));
		}
	}
	else
	{
		if(includeDistortion)
		{
			cv::rectangle(output,config_.cam_right_.ROI_wD_,cv::Scalar(255,0,255));
		}
		else
		{
			cv::rectangle(output,config_.cam_right_.ROI_,cv::Scalar(255,0,255));
		}
	}

	if(display)
	{
		cv::namedWindow("ROI_Interest",cv::WINDOW_NORMAL);
		cv::imshow("ROI_Interest",output);
		cv::waitKey(0);
		cv::destroyWindow("ROI_Interest");
	}
}

void StereoDrawing::drawStereoEpi(cv::Mat left, cv::Mat right, cv::Mat& output,bool withROI)
{
	cv::Mat lRect,rRect;
	stereoRectify(left,lRect,true,true);
	stereoRectify(right,rRect,false,true);
	
			cv::namedWindow("ROI_Interest",cv::WINDOW_NORMAL);
		cv::imshow("ROI_Interest",lRect);
		cv::waitKey(0);
		cv::destroyWindow("ROI_Interest");
	
	cv::Mat lROI,rROI;
	
	
	drawROI(lRect,lROI,false,true,true);
	drawROI(rRect,rROI,false,false,true);
	
				cv::namedWindow("a",cv::WINDOW_NORMAL);
		cv::imshow("a",lROI);
		cv::waitKey(0);
		cv::destroyWindow("a");
	
	output=cv::Mat(cv::Size(lROI.size().width+rROI.size().width,lROI.size().height),lROI.type());
	cv::Mat outl(output,cv::Rect(0,0,lROI.size().width,lROI.size().height));
	cv::Mat outr(output,cv::Rect(lROI.size().width,0,rROI.size().width,rROI.size().height));
	
	lROI.copyTo(outl);
	rROI.copyTo(outr);
	
	//cv::cvtColor(output,output,cv::COLOR_GRAY2RGB);
	
	for(int index=0;index<25;index++)
	{
		int step=lROI.size().height/25.0;
		cv::Point2f leftP(0,index*step);
		cv::Point2f rightP(lROI.size().width+rROI.size().width-1,index*step);
		cv::line(output,leftP,rightP,cv::Scalar(0,255,0));
	}
	
	
}



	
	
}