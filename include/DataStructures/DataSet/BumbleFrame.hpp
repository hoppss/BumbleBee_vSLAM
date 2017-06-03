#ifndef BUMBLE_FRAME_HEADER_HPP
#define BUMBLE_FRAME_HEADER_HPP

#include "DataStructures/DataSet/ImageMetaData.hpp"

namespace stereo
{
	

	
class BumbleFrame
{
	public:
		ImageMetaData leftMeta_,rightMeta_;
		BumbleFrame();
};

}
	


#endif
