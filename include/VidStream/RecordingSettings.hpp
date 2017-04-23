#ifndef FIREWIRE_RECORDING_SETTINGS_HPP
#define FIREWIRE_RECORDING_SETTINGS_HPP

/*internal settings taken from coriander for the bumbleBee*/
#define balanceMAX 63
#define balanceMIN 0
#define expoMAX 1023
#define expoMIN 1
#define brightMAX 255
#define brightMIN 0
#define gainMAX 1023
#define gainMIN 325 



#include <dc1394/dc1394.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>

namespace stereo
{
	
class RecordingSettings
{
	private:
		/*bumbleBee video settings
		 * autoExpose_=  automatically adjust the exposure of the image
		 * autoshutter = automatically adjust the shutter speed
		 * autoGain= automatically sety the ISO gain of the image
		 * whiteBalance_ = automatically balance white colour in image
		 * expose_ = manual exposure settings
		 * ubal_ +vbal_ = manual whitebalance settings
		 * brightness_ = manual brightness settings
		 * shutter_ = speed of shutter
		 * gain_ = manual ISO gain settings
		 * n_buffer= number of circular ring buffers
		 * defaultSet_ = true if using default values (not loaded from XML file)
		 * 
		 * OUTPUTSETTINGS
		 * 
		 * logName_= outputLogFile name
		 * outDir_ =  Root output directory of recordings
		 */
		bool autoExpose_;
		bool autoShutter_;
		bool autoGain_;
		bool whiteBalance_;
		//Manual Input Values
		uint32_t expose_;
		uint32_t ubal_;
		uint32_t vbal_;
		uint32_t brightness_;
		float shutter_;//milliseconds
		uint32_t gain_;
		//Recording settings
		int n_buffer;
		bool defaultSet_;//true if using default camera recording settings
		//outputDirectory Settings
		std::string logDef_;
	public:
		RecordingSettings();
		//input + output file xml
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);	
		//internal camera settings 
		bool validateSettings(); //returns true if input settings are valid (within camera thresholds)
		std::string logName_;
		std::string xmlName_;
		std::string outDir_;
		std::string getxmlDir();

		
};


//These write and read functions must be defined for the serialization in FileStorage to work

static void read(const cv::FileNode& node, stereo::RecordingSettings& x, const stereo::RecordingSettings& default_value = stereo::RecordingSettings()){
if(node.empty())
	{
        x = default_value;
	}
    else
	{
        x.read(node);
	}
}



static void write(cv::FileStorage& fs, const std::string&, const stereo::RecordingSettings& x)
{
    x.write(fs);
}


	
}

#endif