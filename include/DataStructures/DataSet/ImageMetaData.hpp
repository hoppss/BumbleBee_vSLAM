#ifndef IMAGE_META_DATA_HEADER_HPP
#define iMAGE_META_DATA_HEADER_HPP

#include <iostream>
namespace stereo
{
	
class ImageMetaData
{
	public:
		std::string fullDir_;
		std::string fileName_;
		int getTimeStamp() const;
		ImageMetaData();
};
	

}
	


#endif