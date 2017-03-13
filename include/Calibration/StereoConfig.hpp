#ifndef STEREO_CONFIG_HEADER_HPP
#define STEREO_CONFIG_HEADER_HPP

#include "Calibration/SingleOutput.hpp"

namespace stereo
{
class StereoConfig
{
	private:
		std::vector<std::string> removePrefixes(std::vector<std::string> input);
	public:
		StereoConfig();
		SingleConfig config_left_,config_right_;
		SingleOutput output_left_,output_right_;
		bool showIndividualMatches_;
		bool debugInfo_;
		bool compute_rectify_wDist_;//if true, computes the stereorectification mapping including the distortion constants
		bool compute_left_;
		bool compute_right_;
		bool saveIndividualCameras;
		std::string StereoName;//assumes .xml is included in the name
		std::string outputDirectory;
		/// calibration flags
		bool calib_fix_intrinsic_;
		bool calib_guess_intrinsic_;
		bool calib_fix_principal_;
		bool calib_fix_focal_;
		bool calib_fix_aspect_;
		bool calib_same_focal_;
		bool calib_zero_tangent_;
		bool calib_fix_dist_; //for compatability
		bool calib_fix_k1_;
		bool calib_fix_k2_;
		bool calib_fix_k3_;
		bool calib_fix_k4_;
		bool calib_fix_k5_;
		bool calib_fix_k6_;
		bool calib_rational_model_;
		double termination_error_;
		int max_count_;
		bool count_criteria_;
		bool eps_critera_;
		
		int getCalibrationFlags();		
		int getTerminationFlags();
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
		void getMatchesOverlap(std::vector< std::vector<cv::Point2f> > &outLeft,
														std::vector< std::vector<cv::Point2f> > &outright,
														std::vector<int> &leftindex,std::vector<int> &rightindex);//gets all the points where checkerboard pattern is found in both left and right
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