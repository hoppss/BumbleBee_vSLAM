#include "DataStructures/OutputData/StereoFrameStats.hpp"

namespace stereo
{
StereoFrameStats::StereoFrameStats()
{

}
	
bool StereoFrameStats::checkSettings()
{
	if((settings_>=0)&&(settings_<(DETECTION_TIME|CELL_DETECTION_TIME|DESCRIPTION_TIME|OVERALL_TIME|
																ADMIN_TIME|KEEP_OUTLIER|KEEP_PROGRESS|KEEP_RECTIFIED|KEEP_ROI_IMG|KEEP_PRE_REJECTED|KEEP_INPUT)))
	{
		return true;
	}
	else
	{
		return false;
	}
	
	
}
	
	
void StereoFrameStats::setAllOn()
{
settings_=static_cast<featureStats>(DETECTION_TIME|CELL_DETECTION_TIME|DESCRIPTION_TIME|OVERALL_TIME|
																ADMIN_TIME|KEEP_OUTLIER|KEEP_PROGRESS|KEEP_RECTIFIED|KEEP_ROI_IMG|KEEP_PRE_REJECTED|KEEP_INPUT);

}

	
	
}