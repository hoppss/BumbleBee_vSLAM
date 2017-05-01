#include "VidStream/PointGrey.hpp"

namespace stereo 
{

PointGrey::PointGrey()
{
	//	iso_speed=DC1394_ISO_SPEED_400;
	//	frame_rate=DC1394_FRAMERATE_15;
	//	video_mode=DC1394_VIDEO_MODE_1024x768_MONO16;
	//	color_coding=DC1394_COLOR_CODING_MONO16;
	//	n_buffer=8;
	//	autoExpose_=true;
	//	autoShutter_=true;
	//	autoGain_=true;
	//	streaming_=false;
	//	whiteBalance_=false;
	//	
	///	brightness_=1;
	//	shutter_=0.01;
	//	gain_=600;
	//	ubal_=63;
	//	vbal_=20;
	//	expose_=800;
		

		
}

PointGrey::~PointGrey()
{
	//if(init_1394)
//	{
//		closeCamera();
//	}
}

//void PointGrey::setBasicSettings(std::vector<dc1394error_t> &err)
//{
//	err.push_back(dc1394_video_set_iso_speed(camera, iso_speed));
//	err.push_back(dc1394_video_set_mode(camera,video_mode));
//	err.push_back(dc1394_video_set_framerate(camera,frame_rate));
//	err.push_back(dc1394_capture_setup(camera,n_buffer,DC1394_CAPTURE_FLAGS_DEFAULT));

//}

//void PointGrey::setBright(std::vector< dc1394error_t >& err)
//{
	/*always turn on, check within brightness limits*/
	//if((brightness_<=brightMAX)&&(brightness_>=brightMIN))
	//{
	//	err.push_back(DC1394_SUCCESS);
	//}
	//else
	//{
	//	err.push_back(DC1394_FAILURE);
	//}
	//if(checkUpdated(err))
	//{
	//	err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_BRIGHTNESS,DC1394_ON));
	//	err.push_back(dc1394_feature_set_mode(camera,DC1394_FEATURE_BRIGHTNESS,DC1394_FEATURE_MODE_MANUAL));
	//	err.push_back(dc1394_feature_set_value(camera,DC1394_FEATURE_BRIGHTNESS,brightness_));	
	//}
//}

//void PointGrey::setExposure(std::vector< dc1394error_t >& err)
//{
	//if(autoExpose_)
	//{
	//	err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_EXPOSURE,DC1394_ON));
	//	err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_EXPOSURE,DC1394_FEATURE_MODE_AUTO));
	//}
	//else
	//{
		//set mode
	//	if((expose_<=expoMAX)&&(expose_>=expoMIN))
	//	{
	//		err.push_back(dc1394_feature_set_power(camera,DC1394_FEATURE_EXPOSURE,DC1394_ON));
	//		err.push_back(dc1394_feature_set_mode(camera, DC1394_FEATURE_EXPOSURE,DC1394_FEATURE_MODE_MANUAL));
	//		err.push_back(dc1394_feature_set_value(camera, DC1394_FEATURE_EXPOSURE,expose_));
	//	}
	//	else
	//	{
	//		err.push_back(DC1394_FAILURE);
	//	}
//	}
//}
/*
void PointGrey::setGain(std::vector< dc1394error_t >& err)
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


void PointGrey::setShutter(std::vector< dc1394error_t >& err)
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


void PointGrey::setWBalance(std::vector< dc1394error_t >& err)
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


*/

//bool PointGrey::checkUpdated(std::vector< dc1394error_t > err)
//{
	/*cycle through returned error codes, and return false if any of the updates
	 * failed to set*/
//	bool Success=true;
//	for(int index=0;index<err.size();++index)
//	{
//		if(err.at(index)!=DC1394_SUCCESS)
//		{
//			Success=false;
//		}
//	}
//	return Success;
//}



//bool PointGrey::updateSettings()
//{
	/*attempt to change all the settings at once with new values*/
/*	std::vector<dc1394error_t> basic_e,expose_e,balance_e,shutter_e,gain_e,bright_e;
	//holds results of each error code, if any of the vectors are a failure, immediate exit and return false
	setBasicSettings(basic_e);
	if(checkUpdated(basic_e))
	{
		setBright(bright_e);
		if(checkUpdated(bright_e))
		{
			setExposure(expose_e);
			if(checkUpdated(expose_e))
			{
				setGain(gain_e);
				if(checkUpdated(gain_e))
				{
					setShutter(shutter_e);
					if(checkUpdated(shutter_e))
					{
						setWBalance(balance_e);
						if(checkUpdated(balance_e))
						{
							return true;
						}
						else
						{
							std::cerr<<"Shutter Speed Settings failed to configure\n";
							return false;
						}
					}
					else
					{
						std::cerr<<"Shutter Speed Settings failed to configure\n";
						return false;
					}
				}
				else
				{
					std::cerr<<"Gain Settings failed to configure\n";
					return false;
				}
			}
			else
			{
				std::cerr<<"Exposure Settings failed to configure\n";
				return false;
			}
			
		}
		else
		{
			std::cerr<<"Brightness Settings failed to configure\n";
			return false;
		}
		
		
	}
	else
	{
		std::cerr<<"Basic Settings failed to configure\n";
		return false;
	}
}


bool PointGrey::dcinit()
{
	
	bool Error_=true;
	dc1394camera_list_t * list;
	dc1394error_t err;
	init_1394 = dc1394_new (); 
	if(init_1394)
	{	
		std::cout<<"libdc1394 found+initialized -- Success\n";
		err=dc1394_camera_enumerate(init_1394, &list);
		std::cout<<"Camera list found -- "<<dc1394_error_get_string(err)<<std::endl;
		if(err==DC1394_SUCCESS)
		{
			std::cout<<"Cameras Detected --  "<<list->num<<std::endl;
			if(list->num!=0)
			{
				camera = dc1394_camera_new(init_1394, list->ids[0].guid);
				if(camera)
				{
					Error_=false;		
				}
			}
			dc1394_camera_free_list (list);
		}
	}
	else
	{
		std::cerr<<"LIBDC1394 initialization Error"<<std::endl;
	}	
	return Error_;
}


void PointGrey::closeCamera()
{
	dc1394_camera_free(camera);
	dc1394_free(init_1394);
}


void PointGrey::convertToMat(dc1394video_frame_t* src)
{
	memcpy(&stereo_frame,src,sizeof(dc1394video_frame_t)); //copy MetaData
	stereo_frame.allocated_image_bytes=0;
	stereo_frame.image=NULL;

	dc1394_deinterlace_stereo_frames(src,&stereo_frame,DC1394_STEREO_METHOD_INTERLACED);
	//convert images to individual ones, left image on bottom, right image on the top

	d_pt=(short int*)&bayerImage.data[0];
	s_pt=(short int*)&stereo_frame.image[0];
	memcpy(d_pt,s_pt,1536*1024);//copy dc1394 image data into mat structure
	cv::cvtColor(bayerImage,outputImage,CV_BayerBG2GRAY);//debayer into gray colour
	free(s_pt);*/
	/*no need to free the d_pt, as bayer image is constantly overwritten, and has a 
	 * pre-set size specific to the bumblebee camera image*/
	/*
//}


bool PointGrey::openStream()
{
	
	dc1394error_t err=dc1394_video_set_transmission(camera,DC1394_ON);
	std::cout<<"TRANSMISSION -- "<<dc1394_error_get_string(err)<<std::endl;
	if(err==DC1394_SUCCESS)
	{
		streaming_=true;
		return true;
	}
	else
	{
		return false;
	}

}

bool PointGrey::closeStream()
{
	dc1394error_t err=	dc1394_video_set_transmission(camera,DC1394_OFF);
	if(err==DC1394_SUCCESS)
	{
		streaming_=false;
		std::cout<<"Camera Transmission stopped\n";
		return true;
	}
	else
	{
		std::cerr<<"Cannot stop transmission -error- "<<dc1394_error_get_string(err)<<std::endl;	
		return false;
	}
}

bool PointGrey::getLatestFrame(cv::Mat& l, cv::Mat& r)
{
	bool Success=true;
	dc1394video_frame_t * tempFrame;
	dc1394error_t deque,enque;

	
	deque=dc1394_capture_dequeue(camera,DC1394_CAPTURE_POLICY_WAIT,&tempFrame);
	if(deque==DC1394_SUCCESS)
		{
					//check for frame corruption
					if(!dc1394_capture_is_frame_corrupt(camera,tempFrame))
					{
							convertToMat(tempFrame);
							l=left_img;
							r=right_img;
					}
					else
					{
						Success=false;
						std::cerr<<"Frame corrupt -error- \n";
					}
		}
	enque=dc1394_capture_enqueue(camera,tempFrame);
	if(enque!=DC1394_SUCCESS)
	{
		std::cerr<<"Enque -error- "<<dc1394_error_get_string(enque)<<std::endl;	
		Success=false;
	}
	return Success;
}

bool PointGrey::getLatestFrame(cv::Mat& l, cv::Mat& r,uint64_t &stamp)
{
	bool Success=true;
	dc1394error_t deque,enque;

	
	deque=dc1394_capture_dequeue(camera,DC1394_CAPTURE_POLICY_WAIT,&latestFrame);
	
	if(deque==DC1394_SUCCESS)
		{
					//check for frame corruption
					if(!dc1394_capture_is_frame_corrupt(camera,latestFrame))
					{
							stamp=latestFrame->timestamp;
							convertToMat(latestFrame);
							l=left_img;
							r=right_img;
					}
					else
					{
						Success=false;
						std::cerr<<"Frame corrupt -error- \n";
					}
		}
	enque=dc1394_capture_enqueue(camera,latestFrame);
	if(enque!=DC1394_SUCCESS)
	{
		std::cerr<<"Enque -error- "<<dc1394_error_get_string(enque)<<std::endl;	
		Success=false;
	}
	return Success;
}

*/
	
	
	
}