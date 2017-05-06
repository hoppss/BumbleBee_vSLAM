#include "Manager/FireWireSettings.hpp"

namespace stereo {
	
FireWireSettings::FireWireSettings()
{
	autoExpose_=true;
	autoShutter_=false;
	autoGain_=true;
	whiteBalance_=true;
	
	brightness_=1;
	shutter_=0.01;
	gain_=600;
	ubal_=63;
	vbal_=20;
	expose_=800;
	n_buffer=16;
	
	iso_speed=DC1394_ISO_SPEED_400;
	frame_rate=DC1394_FRAMERATE_15;
	video_mode=DC1394_VIDEO_MODE_1024x768_MONO16;
	color_coding=DC1394_COLOR_CODING_MONO16;
}

void FireWireSettings::read(const cv::FileNode& node)
{
	int temp;
	/*Read from XML */
	node["AutoExposure"]>>autoExpose_;
	node["AutoShutter"]>>autoShutter_;
	node["AutoGain"]>>autoGain_;
	node["AutoWhiteBalance"]>>whiteBalance_;
	node["DMA_BufferSize"]>>n_buffer;
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


void FireWireSettings::write(cv::FileStorage& fs) const
{
	/* write to XML*/
	fs<<"{";
	fs<<"AutoExposure"<<autoExpose_;
	fs<<"AutoShutter"<<autoShutter_;
	fs<<"AutoGain"<<autoGain_;
	fs<<"AutoWhiteBalance"<<whiteBalance_;
	fs<<"DMA_BufferSize"<<n_buffer;
	fs<<"ShutterSpeed"<<shutter_;
	fs<<"RAW_gain_val"<<(int)gain_;
	fs<<"RAW_exposure_val"<<(int)expose_;
	fs<<"RAW_vBalance_val"<<(int)vbal_;
	fs<<"RAW_uBalance_val"<<(int)ubal_;
	fs<<"RAW_brightness_val"<<(int)brightness_;
	fs<<"}";
}

///////////////
//raw settings
///////


void FireWireSettings::setBasicSettings(std::vector< dc1394error_t >& err, dc1394camera_t* camera)
{
	err.push_back(dc1394_video_set_transmission(camera,DC1394_OFF));
	err.push_back(dc1394_video_set_iso_speed(camera, iso_speed));
	err.push_back(dc1394_video_set_mode(camera,video_mode));
	err.push_back(dc1394_video_set_framerate(camera,frame_rate));
	err.push_back(dc1394_capture_setup(camera,n_buffer,DC1394_CAPTURE_FLAGS_DEFAULT));
}


void FireWireSettings::setBright(std::vector< dc1394error_t >& err, dc1394camera_t* camera)
{
	if((brightness_<=brightMAX)&&(brightness_>=brightMIN))
	{
		err.push_back(DC1394_SUCCESS);
	}
	else
	{
		err.push_back(DC1394_FAILURE);
	}
	if(checkUpdated(err))
	{
		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_BRIGHTNESS,DC1394_ON));
		err.push_back(dc1394_feature_set_mode(camera,DC1394_FEATURE_BRIGHTNESS,DC1394_FEATURE_MODE_MANUAL));
		err.push_back(dc1394_feature_set_value(camera,DC1394_FEATURE_BRIGHTNESS,brightness_));	
	}
}

void FireWireSettings::setExposure(std::vector< dc1394error_t >& err, dc1394camera_t* camera)
{
	if(autoExpose_)
	{
		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_EXPOSURE,DC1394_ON));
		err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_EXPOSURE,DC1394_FEATURE_MODE_AUTO));
	}
	else
	{
		//set mode
		if((expose_<=expoMAX)&&(expose_>=expoMIN))
		{
			err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_EXPOSURE,DC1394_ON));
			err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_EXPOSURE,DC1394_FEATURE_MODE_MANUAL));
			err.push_back(dc1394_feature_set_value(camera, DC1394_FEATURE_EXPOSURE,expose_));
		}
		else
		{
			err.push_back(DC1394_FAILURE);
		}
	}
}



void FireWireSettings::setGain(std::vector< dc1394error_t >& err, dc1394camera_t* camera)
{
	if(autoGain_)
	{
		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_GAIN,DC1394_ON));
		err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_GAIN,DC1394_FEATURE_MODE_AUTO));
	}
	else
	{
		if((gain_<=gainMAX)&&(gain_>=gainMIN))
		{
			err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_GAIN,DC1394_ON));
			err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_GAIN,DC1394_FEATURE_MODE_MANUAL));
			err.push_back(dc1394_feature_set_value(camera, DC1394_FEATURE_GAIN,gain_));
		}
		else
		{
			err.push_back(DC1394_FAILURE);
		}
	}
}


void FireWireSettings::setShutter(std::vector< dc1394error_t >& err, dc1394camera_t* camera)
{
	if(autoShutter_)
	{
		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_SHUTTER,DC1394_ON));
		err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_SHUTTER,DC1394_FEATURE_MODE_AUTO));
	}
	else
	{
		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_SHUTTER,DC1394_ON));
		err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_SHUTTER,DC1394_FEATURE_MODE_MANUAL));
		err.push_back(dc1394_feature_set_absolute_value(camera,  DC1394_FEATURE_SHUTTER,shutter_));
	}
}


void FireWireSettings::setWBalance(std::vector< dc1394error_t >& err, dc1394camera_t* camera)
{
	if(whiteBalance_)
	{
		if((ubal_<=balanceMAX)&&(ubal_>=balanceMIN)&&(vbal_<=balanceMAX)&&(vbal_>=balanceMIN))
		{
			err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_WHITE_BALANCE,DC1394_ON));
			err.push_back(dc1394_feature_set_mode(camera,DC1394_FEATURE_WHITE_BALANCE,DC1394_FEATURE_MODE_MANUAL));
			err.push_back(dc1394_feature_whitebalance_set_value(camera,ubal_,vbal_));
		}
		else
		{
			err.push_back(DC1394_FAILURE);
		}
		
		
	}
	else
	{
		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_WHITE_BALANCE,DC1394_OFF));
	}
}


bool FireWireSettings::checkUpdated(std::vector< dc1394error_t > err)
{
	//cycle through returned error codes, and return false if any of the updates
	//failed to set//
	//To be used for each type of setting uploaded to the bumbleBee camera
	//if any of the settings failed to be set by the camera firmware, false is returned
	bool Success=true;
	for(int index=0;index<err.size();++index)
	{
		if(err.at(index)!=DC1394_SUCCESS)
		{
			Success=false;
		}
	}
	return Success;
}



	

}
