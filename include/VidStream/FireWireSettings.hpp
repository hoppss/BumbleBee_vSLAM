#ifndef FIREWIRE_STREAM_SETTINGS_HEADER_HPP
#define FIREWIRE_STREAM_SETTINGS_HEADER_HPP

#include <dc1394/dc1394.h>
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>


namespace stereo
{
	
	class FireWireSettings
	{
		private:
			std::string printMode(dc1394feature_mode_t mod);
		public:
			FireWireSettings();
			dc1394speed_t iso_speed;
			dc1394framerate_t frame_rate;
			dc1394video_mode_t video_mode;
			dc1394color_coding_t color_coding;
			dc1394feature_info_t bright;
			dc1394feature_info_t auto_exposure;
			dc1394feature_info_t	white_balance;
			dc1394feature_info_t	shutter;
			dc1394feature_info_t	gain;
			int n_buffer;
			void printConfig(dc1394featureset_t set);
			void printFeature(dc1394feature_info_t pr);
			void printAvailable(dc1394featureset_t set);
	};

}

#endif