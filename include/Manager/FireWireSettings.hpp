#ifndef FIREWIRE_SETTTINGS_HEADER_HPP
#define FIREWIRE_SETTINGS_HEADER_HPP

#include <dc1394/dc1394.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


//////////////////////
////////Camera Settings Definitions
//////////////////////
#define balanceMAX 63
#define balanceMIN 0
#define expoMAX 1023
#define expoMIN 1
#define brightMAX 255
#define brightMIN 0
#define gainMAX 1023
#define gainMIN 325 
//Taken from Coriander GUI



namespace stereo
{
	
class FireWireSettings
{
	private:
		dc1394speed_t iso_speed; /*always the same i.e. they arent going to be changed*/
		
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
		
		dc1394framerate_t frame_rate;
		dc1394video_mode_t video_mode;
		dc1394color_coding_t color_coding;
		
	public:
		FireWireSettings();
		 void write(cv::FileStorage& fs) const;
		 void read(const cv::FileNode& node);
		 bool checkUpdated(std::vector<dc1394error_t> err);
		 void setBasicSettings(std::vector<dc1394error_t> &err,dc1394camera_t *camera);
	   void setExposure(std::vector<dc1394error_t> &err,dc1394camera_t *camera);
		 void setWBalance(std::vector<dc1394error_t> &err,dc1394camera_t *camera);
		 void setShutter(std::vector<dc1394error_t> &err,dc1394camera_t *camera);
		 void setGain(std::vector<dc1394error_t> &err,dc1394camera_t *camera);
 		 void setBright(std::vector<dc1394error_t> &err,dc1394camera_t *camera);
		 friend class FireWireManager;
};
	
//These write and read functions must be defined for the serialization in FileStorage to work
static void write(cv::FileStorage& fs, const std::string&, const FireWireSettings& x)
{
    x.write(fs);
}
static void read(const cv::FileNode& node, FireWireSettings& x, const FireWireSettings& default_value = FireWireSettings()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

	
	
}


#endif