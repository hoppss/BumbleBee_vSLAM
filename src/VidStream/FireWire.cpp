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
					//	newSettings.printAvailable(temp);
						
						
			//				int TotalFeatures;
	//TotalFeatures=sizeof(temp)/sizeof(dc1394feature_info_t);
//	std::cout<<"features det "<<TotalFeatures<<std::endl;

					
				/*		printf("Using camera with GUID %"PRIx64"\n", camera->guid);
						
						dc1394bool_t a ;
						std::cout<<"found "<<a<<std::endl;
						dc1394_feature_is_present(camera,DC1394_FEATURE_BRIGHTNESS,&a);
						std::cout<<"found "<<a<<std::endl;
						
						dc1394feature_info_t b;
						dc1394_feature_get(camera,&b);
						
						dc1394_feature_print(&b,ptr);*/

						//newSettings.features_set.
						
		/*				
						typedef struct __dc1394feature_info_t_struct
{
    dc1394feature_t    id;
    dc1394bool_t       available;
    dc1394bool_t       absolute_capable;
    dc1394bool_t       readout_capable;
    dc1394bool_t       on_off_capable;
    dc1394bool_t       polarity_capable;
    dc1394switch_t     is_on;
    dc1394feature_mode_t     current_mode;
    dc1394feature_modes_t    modes;
    dc1394trigger_modes_t    trigger_modes;
    dc1394trigger_mode_t     trigger_mode;
    dc1394trigger_polarity_t trigger_polarity;
    dc1394trigger_sources_t  trigger_sources;
    dc1394trigger_source_t   trigger_source;
    uint32_t           min;
    uint32_t           max;
    uint32_t           value;
    uint32_t           BU_value;
    uint32_t           RV_value;
    uint32_t           B_value;
    uint32_t           R_value;
    uint32_t           G_value;
    uint32_t           target_value;

    dc1394switch_t     abs_control;
    float              abs_value;
    float              abs_max;
    float              abs_min;

} dc1394feature_info_t;
						*/
						
						
						//brightness etc...

						/*err=dc1394_video_set_iso_speed(camera, DC1394_ISO_SPEED_400);
						std::cout<<"ISO SPEED 400 -- "<<dc1394_error_get_string(err)<<std::endl;
						err=dc1394_video_set_mode(camera, DC1394_VIDEO_MODE_1024x768_MONO16);
						std::cout<<"MODE set 1024x768 MONO16 -- "<<dc1394_error_get_string(err)<<std::endl;
						err=dc1394_video_set_framerate(camera, DC1394_FRAMERATE_15);
						std::cout<<"15 FPS -- "<<dc1394_error_get_string(err)<<std::endl;
						err=dc1394_capture_setup(camera,1, DC1394_CAPTURE_FLAGS_DEFAULT);
						std::cout<<"capture setup -- "<<dc1394_error_get_string(err)<<std::endl;
						bayerImage=cv::Mat(1536,1024,CV_8UC1);
						outputImage=cv::Mat(1536,1024,CV_8UC1);
						
						
						left_img=outputImage(cv::Rect(0,768,1024,768));
						right_img=outputImage(cv::Rect(0,0,1024,768));
						
						
						initialized_=true;*/
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

bool FireWire::firewireSetup(FireWireSettings set)
{
	bool ans=true;
	dc1394error_t brightness,exposure,white_balance,shutter,gain,trigger; //features set
	dc1394error_t speed,mode,framerate,capture_setup;

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



void FireWire::defaultSetup()
{

		
}


	
}