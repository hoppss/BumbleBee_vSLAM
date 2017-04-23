#ifndef VIDEO_MANAGER_HEADER_HPP
#define VIDEO_MANAGER_HEADER_HPP


//#include <boost/filesystem.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>

#include <curses.h>
#include <stdlib.h> 

//#include <easylogging++.h>
#include "VidStream/PointGrey.hpp"

////////////////////////////////////////////
//constants that define output names for a variety of functions
#define LEFT_PREFIX "l" //prefix for images stored as l_filename.ppm
#define RIGHT_PREFIX "r"
#define IMAGE_PREFIX "recording"
#define IMAGE_LEFT_FOLDER "Left" //left images will be stored under this directory
	// i.e ROOT_DIR_INPUT/IMAGE_PREFIX/Left/l_filename.ppm
#define IMAGE_RIGHT_FOLDER "Right"





/////////////////////////////////
//logging constant variables
#define LOGGING_PREFIX "Logging"
// i.e ROOT_DIR_INPUT/LOGGING_PREFIX/.....All logs
#define DC1394_LOG_NAME "dcLog"
#define MAT_OUTPUT_LOG_NAME "MatLog"
#define SYSTEM_LOG_NAME "system"
/////////////////////////////////
//hold the names of all the output log files to be stored under
// ROOT_DIR_INPUT/LOGGING_PREFIX/{logs}



#define DC1394_LOGGER "/media/ubuntu/SD_CARD/Logging/DC1394.conf"
#define MAT_LOGGER "/media/ubuntu/SD_CARD/Logging/Mat.conf"
#define SYSTEM_LOGGER "/media/ubuntu/SD_CARD/Logging/Default.conf"
////////////////////////////////////
// these define the logging configurations i.e the formatting for each one

#include "spdlog/spdlog.h"
#include "VidStream/RecordingSettings.hpp"

#include <boost/thread.hpp>
#include <queue>


namespace stereo
{

class VideoManager
{
	private:
		RecordingSettings recConfig_;//basic configuration of the camera
		
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
		boost::thread* recordThread_,*leftCopyThread_,*rightCopyThread_;
		boost::mutex mutexLeftQueue_,mutexRightQueue_;
		std::queue<cv::Mat> rightImgs_;
		/***
		 * Internal Functions for configuring the bumblebee camera */
		void setExposure(std::vector<dc1394error_t> &err);
		void setWBalance(std::vector<dc1394error_t> &err);
		void setShutter(std::vector<dc1394error_t> &err);
		void setGain(std::vector<dc1394error_t> &err);
 		void setBright(std::vector<dc1394error_t> &err);
		/*
		 * Internal utility Functions
		 */
		bool checkForError(std::vector<dc1394error_t> &err);
		
		void LatestFrame();
		void saveFrame();
		bool recording_;
	public:
		std::queue<int> leftImgs_;
		enum VIDEO_INPUT_TYPE
		{
			POINTGREY
		};
		std::shared_ptr<spdlog::logger> my_logger=spdlog::basic_logger_mt("system", "/media/ubuntu/SD_CARD/Logging/out");
		VideoManager();
		~VideoManager();
		void startRecording();
		void stopRecording();
			
};

	
	
}

#endif
