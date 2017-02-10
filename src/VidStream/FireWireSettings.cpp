#include "VidStream/FireWireSettings.hpp"
#include <VidStream/FireWire.hpp>

namespace stereo{
	
FireWireSettings::FireWireSettings()
{
		iso_speed=DC1394_ISO_SPEED_400;
		frame_rate=DC1394_FRAMERATE_15;
		video_mode=DC1394_VIDEO_MODE_1024x768_MONO16;
		color_coding=DC1394_COLOR_CODING_MONO16;
		n_buffer=2;
}

void FireWireSettings::printConfig(dc1394featureset_t set)
{
	int TotalFeatures;
	TotalFeatures=sizeof(set)/sizeof(dc1394feature_info_t);
	for(int index=0;index<TotalFeatures;index++)
	{
		printFeature(set.feature[index]);
	}
}

void FireWireSettings::printFeature(dc1394feature_info_t pr)
{
	std::cout<<"Feature Name: "<<dc1394_feature_get_string(pr.id)<<std::endl;
	
}

std::string FireWireSettings::printMode(dc1394feature_mode_t mod)
{
	std::string Ans="";
	switch(mod)
	{
		case DC1394_FEATURE_MODE_MANUAL : 
		{
			Ans="DC1394_FEATURE_MODE_MANUAL";
			break;
		}
		case DC1394_FEATURE_MODE_AUTO :
		{
			Ans="DC1394_FEATURE_MODE_AUTO ";
			break;
		}
		case DC1394_FEATURE_MODE_ONE_PUSH_AUTO :
		{
			Ans="DC1394_FEATURE_MODE_ONE_PUSH_AUTO";
			break;
		}
	}
	return Ans;
}



void FireWireSettings::printAvailable(dc1394featureset_t set)
{
	std::string available,unavailable;
	available="";
	unavailable="";
	int TotalFeatures;
	TotalFeatures=sizeof(set)/sizeof(dc1394feature_info_t);
	for(int index=0;index<TotalFeatures;index++)
	{
		if(set.feature[index].available)
		{
			available+=dc1394_feature_get_string(set.feature[index].id);
			available+=" -- Available\n";
		}
		else
		{
			unavailable+=dc1394_feature_get_string(set.feature[index].id);
			unavailable+=" -- Not Found\n";
		}
	}
	
	std::cout<<"Camera Functions ------------\n";
	std::cout<<available<<unavailable<<"\n------------\n";
	
}





}