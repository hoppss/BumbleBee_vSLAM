#include "VidStream/RecordingSettings.hpp"

namespace stereo {

RecordingSettings::RecordingSettings()
{
		n_buffer=18;
		autoExpose_=true;
		autoShutter_=true;
		autoGain_=true;
		whiteBalance_=false;
		
		brightness_=1;
		shutter_=0.01;
		gain_=600;
		ubal_=63;
		vbal_=20;
		expose_=800;
		
		defaultSet_=true;

		
		logName_="myLog";
		outDir_="/media/ubuntu/SD_CARD/Logging";
		xmlName_="RecordingSettings.xml";
		
}


//input + output file xml
////////////////////////
void RecordingSettings::read(const cv::FileNode& node)
{

	int temp;
	/*Read from XML */
	node["OutputRootDirectory"]>>outDir_;
	node["LoggingFileName"]>>logName_;
	node["AutoExposure"]>>autoExpose_;
	node["AutoShutter"]>>autoShutter_;
	node["AutoGain"]>>autoGain_;
	node["AutoWhiteBalance"]>>whiteBalance_;
	node["DMA_Buffer"]>>n_buffer;
	node["ShutterSpeed"]>>shutter_;
	node["RAW_gain_val"]>>temp;
	gain_=static_cast<uint32_t>(temp);
	node["RAW_exposure_val"]>>temp;
	expose_=static_cast<uint32_t>(temp);
	node["RAW_vBalance_val"]>>temp;
	vbal_=static_cast<uint32_t>(temp);
	node["RAW_uBalance_val"]>>temp;
	ubal_=static_cast<uint32_t>(temp);
	node["RAW_brightness_val"]>>temp;
	brightness_=static_cast<uint32_t>(temp);
}

void RecordingSettings::write(cv::FileStorage& fs) const
{
		/* write to XML*/
	fs<<"{";
	fs<<"OutputRootDirectory"<<outDir_;
	fs<<"LoggingFileName"<<logName_;
	fs<<"AutoExposure"<<autoExpose_;
	fs<<"AutoShutter"<<autoShutter_;
	fs<<"AutoGain"<<autoGain_;
	fs<<"AutoWhiteBalance"<<whiteBalance_;
	fs<<"DMA_Buffer"<<n_buffer;
	fs<<"ShutterSpeed"<<shutter_;
	fs<<"RAW_gain_val"<<(int)gain_;
	fs<<"RAW_exposure_val"<<(int)expose_;
	fs<<"RAW_vBalance_val"<<(int)vbal_;
	fs<<"RAW_uBalance_val"<<(int)ubal_;
	fs<<"RAW_brightness_val"<<(int)brightness_;
	fs<<"}";

}

std::string RecordingSettings::getxmlDir()
{
	return outDir_+"/"+xmlName_;
}



bool RecordingSettings::validateSettings()
{
	bool Success_;
	return Success_;
}


}