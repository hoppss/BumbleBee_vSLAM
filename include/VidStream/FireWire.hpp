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
 * Specially adapted to fit the BumbleBee 
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
		bool firewireSetup(FireWireSettings set);
		void convertToMat(dc1394video_frame_t * src);
		void closeAndFreeMem();
	public:
		FireWire();
		FireWire(FireWireSettings set);
		~FireWire();
		bool scanNewCamera(FireWireSettings &newSettings);
		bool scanAvailableSettings(FireWireSettings &output);
		bool singleCapture(cv::Mat &output);
		bool singleCapture(cv::Mat &l,cv::Mat &r);
		bool getLatestFrame(cv::Mat &l,cv::Mat &r);
		bool getLatestFrame(cv::Mat &l,cv::Mat &r,uint64_t &stamp);
		bool streamStop();
		bool openStream();
	};
	
}
#endif

