#include "VidStream/FireWire.hpp"

namespace stereo{
	
FireWire::FireWire()
{
	//default constructor, scans camera and creates Settings
	FireWireSettings Ans;
	scanNewCamera(Ans);
	
	
}

bool FireWire::scanNewCamera(FireWireSettings &newSettings)
{
	bool Error_=true;
	dc1394camera_list_t * list;
	dc1394error_t err;
	
	std::cout<<"Scanning for new FireWire Camera\n---------------\n";
	init_1394 = dc1394_new (); 
	if(init_1394) //checks if initialized, returns error message otherwise
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
						
						
						printf("Using camera with GUID %"PRIx64"\n", camera->guid);
						
						dc1394featureset_t temp;
						dc1394_feature_get_all(camera,&temp);
						
						firewireSetup(newSettings);

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

FireWire::~FireWire()
{
	closeAndFreeMem();
}


bool FireWire::firewireSetup(FireWireSettings set)
{
	bool ans=true;
	dc1394error_t brightness,exposure,white_balance,shutter,gain,trigger; //features set
	dc1394error_t speed,mode,framerate,capture_setup;
	
	bayerImage=cv::Mat(1536,1024,CV_8UC1);
	outputImage=cv::Mat(1536,1024,CV_8UC1);
	left_img=outputImage(cv::Rect(0,768,1024,768));
	right_img=outputImage(cv::Rect(0,0,1024,768));

	speed=dc1394_video_set_iso_speed(camera, set.iso_speed);
	mode=dc1394_video_set_mode(camera,set.video_mode);
	framerate=dc1394_video_set_framerate(camera,set.frame_rate);
	capture_setup=dc1394_capture_setup(camera,set.n_buffer,DC1394_CAPTURE_FLAGS_DEFAULT);
	
	
	//check for errors
	if((speed!=DC1394_SUCCESS)&&(ans==true))
	{
		ans=false;
		std::cout<<"FireWire setup error -- "<<dc1394_error_get_string(speed)<<std::endl;
	}
		if((mode!=DC1394_SUCCESS)&&(ans==true))
	{
		ans=false;
		std::cout<<"FireWire setup error -- "<<dc1394_error_get_string(mode)<<std::endl;
	}
		if((framerate!=DC1394_SUCCESS)&&(ans==true))
	{
		ans=false;
		std::cout<<"FireWire setup error -- "<<dc1394_error_get_string(framerate)<<std::endl;
	}
		if((capture_setup!=DC1394_SUCCESS)&&(ans==true))
	{
		ans=false;
		std::cout<<"FireWire setup error -- "<<dc1394_error_get_string(capture_setup)<<std::endl;
	}
	
	
	
	if(ans)
	{
		std::cout<<"FireWire setup Completed"<<std::endl;
	}

	return ans;
	
}


bool FireWire::singleCapture(cv::Mat& output)
{
	bool Success=false;
	dc1394video_frame_t * tempFrame;	
	if(openStream())
	{
		dc1394error_t err=dc1394_capture_dequeue(camera,DC1394_CAPTURE_POLICY_WAIT,&tempFrame);
		if(err==DC1394_SUCCESS)
		{
					//check for frame corruption
					if(!dc1394_capture_is_frame_corrupt(camera,tempFrame))
					{
							convertToMat(tempFrame);
							output=outputImage;
					}
		}
		err=dc1394_capture_enqueue(camera,tempFrame);
		streamStop();	
	}
	
	return Success;
}

bool FireWire::singleCapture(cv::Mat& l, cv::Mat& r)
{
	bool Success=false;
	dc1394video_frame_t * tempFrame;	
	if(openStream())
	{
		dc1394error_t err=dc1394_capture_dequeue(camera,DC1394_CAPTURE_POLICY_WAIT,&tempFrame);
		if(err==DC1394_SUCCESS)
		{
					//check for frame corruption
					if(!dc1394_capture_is_frame_corrupt(camera,tempFrame))
					{
							convertToMat(tempFrame);
							l=left_img;
							r=right_img;
					}
		}
		err=dc1394_capture_enqueue(camera,tempFrame);
		streamStop();	
	}
	
	return Success;
}




void FireWire::convertToMat(dc1394video_frame_t * src)
{
	dc1394video_frame_t stereo_frame;
	memcpy(&stereo_frame,src,sizeof(dc1394video_frame_t)); //copy MetaData
	stereo_frame.allocated_image_bytes=0;
	stereo_frame.image=NULL;

	dc1394_deinterlace_stereo_frames(src,&stereo_frame,DC1394_STEREO_METHOD_INTERLACED);
	//convert images to individual ones, left image on bottom, right image on the top

	short int * d_pt;
 	short int * s_pt;

	d_pt=(short int*)&bayerImage.data[0];
	s_pt=(short int*)&stereo_frame.image[0];
	memcpy(d_pt,s_pt,1536*1024);//copy dc1394 image data into mat structure
	cv::cvtColor(bayerImage,outputImage,CV_BayerBG2GRAY);//debayer into gray colour
}




bool FireWire::openStream()
{
	
	dc1394error_t err=dc1394_video_set_transmission(camera,DC1394_ON);
	std::cout<<"TRANSMISSION -- "<<dc1394_error_get_string(err)<<std::endl;
	if(err==DC1394_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool FireWire::streamStop()
{
	dc1394error_t err=	dc1394_video_set_transmission(camera,DC1394_OFF);
	if(err==DC1394_SUCCESS)
	{
		std::cout<<"Camera Transmission stopped\n";
		return true;
	}
	else
	{
		std::cerr<<"Cannot stop transmission -error- "<<dc1394_error_get_string(err)<<std::endl;	
		return false;
	}
}

void FireWire::closeAndFreeMem()
{
	dc1394error_t capture;
	
	capture=dc1394_capture_stop(camera);
	dc1394_camera_free(camera);
	dc1394_free(init_1394);
	
	
	if(capture!=DC1394_SUCCESS)
	{
		std::cerr<<"Cannot stop capture -error- "<<dc1394_error_get_string(capture)<<std::endl;	
	}

}

bool FireWire::getLatestFrame(cv::Mat& l, cv::Mat& r)
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


}