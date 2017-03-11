#ifndef FIREWIRE_MANAGER_HEADER_HPP
#define FIREWIRE_MANAGER_HEADER_HPP

#include "VidStream/FireWire.hpp"
#include "FrontEnd/StereoFeatures/StereoFeatures.hpp"

#include "Analysis/SimpleFeedback.hpp"


namespace stereo
{
	/* real time manager for the firewire camera set*/
class FWmanager
{
	public:
		FWmanager();
		FireWire bumbleBee_;
		StereoInternal FrontEnd_config;
		void singleDisplay();
};
}

#endif