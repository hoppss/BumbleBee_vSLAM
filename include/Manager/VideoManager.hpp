#ifndef VIDEO_MANAGER_HEADER_HPP
#define VIDEO_MANAGER_HEADER_HPP

#include <curses.h>
#include <stdlib.h> 

#include <time.h>
#include <iostream>
#include <boost/filesystem.hpp>

#include "VidStream/PointGrey.hpp"
#include "Manager/FireWireManager.hpp"

////////////////////////////
//Define all the default settings if not xml input is specefied
///////////////////////////////



#define DEFAULT_ROOT_IN_ "/home/ubuntu/ConfigurationFiles/Recording"
#define DEFAULT_ROOT_OUT_ "/media/usb0/Recordings"
#define DEFAULT_XML_NAME_ "RecordingSettings.xml"
#define DEFAULT_SYSTEM_LOG_NAME_ "sys.recordLog"
#define DEFAULT_CAMERA_LOG_NAME_ "bumbleBee.recordLog"
#define DEFAULT_IN_OUT_LOG_NAME_ "nCurses.recordLog"
#define DEFAULT_LOG_FOLDER_ "logging"
#define DEFAULT_DATA_FOLDER_ "data"
#define DEFAULT_LEFTCAMERA_FOLDER_ "left"
#define DEFAULT_RIGHTCAMERA_FOLDER_ "right"



		
		
		/*cv::Mat bayerImage=cv::Mat(1536,1024,CV_8UC1);
		cv::Mat outputImage=cv::Mat(1536,1024,CV_8UC1);
		cv::Mat left_img=outputImage(cv::Rect(0,768,1024,768));
		cv::Mat right_img=outputImage(cv::Rect(0,0,1024,768));
		dc1394video_frame_t * latestFrame;
		dc1394video_frame_t stereo_frame;
		short int * d_pt;
		short int * s_pt;
		dc1394_t * init_1394;//is the camera properly set up
		dc1394camera_t *camera;//reference to camera
		dc1394speed_t iso_speed;
		dc1394framerate_t frame_rate;
		dc1394video_mode_t video_mode;
		dc1394color_coding_t color_coding;
		boost::thread* recordThread_,*leftCopyThread_,*rightCopyThread_;
		boost::mutex mutexLeftQueue_,mutexRightQueue_;
		std::queue<cv::Mat> rightImgs_;

		  Internal Functions for configuring the bumblebee camera 
		void setExposure(std::vector<dc1394error_t> &err);
		void setWBalance(std::vector<dc1394error_t> &err);
		void setShutter(std::vector<dc1394error_t> &err);
		void setGain(std::vector<dc1394error_t> &err);
 		void setBright(std::vector<dc1394error_t> &err);

		 */
		
		
	//	bool checkForError(std::vector<dc1394error_t> &err);
		
	//	void LatestFrame();
	//	void saveFrame();
	//	bool recording_;


// these define the logging configurations i.e the formatting for each one

#include "spdlog/spdlog.h"
#include "VidStream/RecordingSettings.hpp"

#include <boost/thread.hpp>
#include <queue>


namespace stereo
{
	
typedef boost::shared_lock<boost::shared_mutex>  ReadLock;
typedef boost::unique_lock<boost::shared_mutex> WriteLock;

class VideoManager
{
	private:
		enum DIRECTNAME
		{
			rootRecordDir,
			rootTimeDir,
			rootLog,
			rootData,
			syslog,
			camlog,
			inoutlog,
			rootLfolder,
			rootRfolder
		};
		RecordingSettings recConfig_;//basic configuration of the camera
		///////////////
		///Directory and output variables
		////////////////
		std::string root_in_dir_;//overall input directory
		std::string root_out_dir_;//overall output directory
		//folder Names
		std::string log_folder_;
		std::string data_folder_;
		std::string l_image_folder_;
		std::string r_image_folder_;
		//filenames
		std::string syslogName_;
		std::string camlogName_;
		std::string inoutlogName_;
		//dynamic variables
		time_t starting_time;
		
		///////////////////////////
		//utility functions
		void setDefaultOutvar();
		std::string getStringFormat(time_t inTime);
		bool initFiles();
		std::string genfullDir(DIRECTNAME type);
		bool createDir(std::string dir);
		
		// State Variables + logging 
		std::shared_ptr<spdlog::logger> oLog;
		bool Initialized_;//true if there were no errors from loading files
		bool Terminate_;//has a shared mutex associated with it, true if user signaled the program to end
		//Thread Classes and Locks
		boost::thread *pollThread_; 
		FireWireManager *bumbleBee_;
		
		//pollThread continously checks for user input
		boost::thread *managerThread_;
		//managerThread, the overall VideoManager thread that monitors all the processes,
		//and spawns/terminates processes
		boost::shared_mutex mutexTerminate_;
		//Threaded Functions
		
		void pollThread();
		void mainManagerThread();
	public:
		VideoManager();
		VideoManager(std::string RecordingSettingsDirectory);
		~VideoManager();
	//Control functions
		void beginRecording();
			
};

	
	
}

#endif
