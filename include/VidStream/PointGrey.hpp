#ifndef POINT_GREY_BUMBLEBEE_HEADER_HPP
#define POINT_GREY_BUMBLEBEE_HEADER_HPP

#include <dc1394/dc1394.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#define balanceMAX 63
#define balanceMIN 0
#define expoMAX 1023
#define expoMIN 1
#define brightMAX 255
#define brightMIN 0
#define gainMAX 1023
#define gainMIN 325 
/*from coriander*/


namespace stereo
{
class PointGrey
{
	private:
		cv::Mat bayerImage=cv::Mat(1536,1024,CV_8UC1);
		cv::Mat outputImage=cv::Mat(1536,1024,CV_8UC1);
		cv::Mat left_img=outputImage(cv::Rect(0,768,1024,768));
		cv::Mat right_img=outputImage(cv::Rect(0,0,1024,768));
		dc1394video_frame_t * latestFrame;
		dc1394video_frame_t stereo_frame;
		short int * d_pt;
		short int * s_pt;
		dc1394_t * init_1394;//is the camera properly set up
		dc1394camera_t *camera;//reference to camera
		dc1394speed_t iso_speed; /*always the same i.e. they arent going to be changed*/
		dc1394framerate_t frame_rate;
		dc1394video_mode_t video_mode;
		dc1394color_coding_t color_coding;
		/*settings available*/
		bool streaming_;
		void setBasicSettings(std::vector<dc1394error_t> &err);
		void setExposure(std::vector<dc1394error_t> &err);
		void setWBalance(std::vector<dc1394error_t> &err);
		void setShutter(std::vector<dc1394error_t> &err);
		void setGain(std::vector<dc1394error_t> &err);
 		void setBright(std::vector<dc1394error_t> &err);
		void convertToMat(dc1394video_frame_t * src);
		bool checkUpdated(std::vector<dc1394error_t> err);
	public:
		bool autoExpose_;
		bool autoShutter_;
		bool autoGain_;
		bool whiteBalance_;
		uint32_t expose_;
		uint32_t ubal_;
		uint32_t vbal_;
		uint32_t brightness_; //always balance the image
		float shutter_;
		uint32_t gain_;
		int n_buffer;
		void closeCamera();
		bool updateSettings();
		bool openStream();
		bool closeStream();
		bool dcinit();
		bool getLatestFrame(cv::Mat& l, cv::Mat& r);
		bool getLatestFrame(cv::Mat &l,cv::Mat &r,uint64_t &stamp);
		PointGrey();
		~PointGrey();
};
	
}

#endif