#include "Calibration/StereoConfig.hpp"

namespace stereo
{	
	
StereoConfig::StereoConfig()
{
	
}
	
void StereoConfig::read(const cv::FileNode& node)
{
	node["compute_right"]>>compute_right_;
	node["compute_left"]>>compute_left_;
	node["compute_rectify"]>>compute_rectify_;
	node["debug_info"]>>debugInfo_;
	node["showIndiv"]>>showIndividualMatches_;
	if(compute_left_)
	{
		node["leftConfig"]>>config_left_;
	}
	node["leftOutput"]>>output_left_;
	if(compute_right_)
	{
		node["rightconfig"]>>config_right_;
	}
	node["rightOutput"]>>output_right_;

}

void StereoConfig::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"compute_right"<<compute_right_;
	fs<<"compute_left"<<compute_left_;
	fs<<"compute_rectify"<<compute_rectify_;
	fs<<"debug_info"<<debugInfo_;
	fs<<"showIndiv"<<showIndividualMatches_;	
	if(compute_left_)
	{
		fs<<"leftConfig"<<config_left_;
	}
	fs<<"leftOutput"<<output_left_;
	if(compute_right_)
	{
		fs<<"rightconfig"<<config_right_;
	}
	fs<<"rightOutput"<<output_right_;
	fs<<"}";
}

void StereoConfig::getMatchesOverlap(std::vector< std::vector< cv::Point2f > >& outLeft, std::vector< std::vector< cv::Point2f > >& outright)
{

}


	
	
}