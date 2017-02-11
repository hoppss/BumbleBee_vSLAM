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

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
		
		cv::Mat left_img,right_img;
		cv::Mat bayerImage,outputImage;;
		bool openStream();
		bool firewireSetup(FireWireSettings set);
		void convertToMat(dc1394video_frame_t * src,cv::Mat &dest);
		void closeAndFreeMem();
	public:
		FireWire();
		~FireWire();
		FireWire(std::string config_dir);
		void streamPause();
	//	bool getLatestImage(cv::Mat &fin);
		bool scanNewCamera(FireWireSettings &newSettings);
		bool singleCapture(cv::Mat &output);
		bool streamStop();
	};
	
}
#endif

