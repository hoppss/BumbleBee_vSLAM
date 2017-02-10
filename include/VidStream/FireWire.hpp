#ifndef VIDSTREAM_FIREWIRE_HEADER_HPP
#define VIDSTREAM_FIREWIRE_HEADER_HPP

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <endian.h>

#ifndef _WIN32
#include <unistd.h>
#endif


#include "VidStream/FireWireSettings.hpp"
/******************
 * Code adapated from Damien Douxchamps and the libdc1394 library
 * */


namespace stereo{
	class FireWire
	{
		private:
		dc1394featureset_t features;
		dc1394camera_t *camera;
		dc1394_t * init_1394;
		bool initialized_;
		//Video Global Variables
 		dc1394video_frame_t * latest_frame;
		dc1394video_frame_t stereo_frame;
	//	cv::Mat left_img,right_img;
	//	cv::Mat outputImage,bayerImage;
		void cleanup_and_exit(dc1394camera_t *camera);
		void clearFrame();
		int img_width_,img_height_;
		bool openStream();
		void defaultSetup();
		bool firewireSetup(FireWireSettings set);
	public:
		FireWire();
		FireWire(std::string config_dir);
		void streamPause();
	//	bool getLatestImage(cv::Mat &fin);
		void streamStop(bool close);
		bool scanNewCamera(FireWireSettings &newSettings);
	};
	
}
#endif

