#ifndef STEREO_CONFIG_HEADER_HPP
#define STEREO_CONFIG_HEADER_HPP

#include "Calibration/SingleOutput.hpp"

namespace stereo
{
class StereoConfig
{
	private:
		
	public:
		StereoConfig();
		SingleConfig config_left_,config_right_;
		SingleOutput output_left_,output_right_;
		bool showIndividualMatches_;
		bool debugInfo_;
		bool compute_rectify_;
		bool compute_left_;
		bool compute_right_;
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
		void getMatchesOverlap(std::vector< std::vector<cv::Point2f> > &outLeft,
														std::vector< std::vector<cv::Point2f> > &outright);//gets all the points where checkerboard pattern is found in both left and right
};


static void read(const cv::FileNode& node, stereo::StereoConfig& x, const stereo::StereoConfig& default_value = stereo::StereoConfig()){
   if(node.empty())
	{
        x = default_value;
	}
    else
	{
        x.read(node);
	}
}

static void write(cv::FileStorage& fs, const std::string&, const stereo::StereoConfig& x)
{
    x.write(fs);
}

}
	


#endif