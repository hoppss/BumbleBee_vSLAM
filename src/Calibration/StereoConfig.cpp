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
	node["compute_rectify_wDist"]>>compute_rectify_wDist_;
	
	node["debug_info"]>>debugInfo_;
	node["showIndiv"]>>showIndividualMatches_;
	node["fix_intrinsic"]>>calib_fix_intrinsic_;
	node["guess_intrinsic"]>>calib_guess_intrinsic_;
	node["fix_principal"]>>calib_fix_principal_;
	node["fix_focal"]>>calib_fix_focal_;
	node["fix_aspect"]>>calib_fix_aspect_;
	node["same_focal"]>>calib_same_focal_;
	node["zero_tangent"]>>calib_zero_tangent_;
	node["fix_dist"]>>calib_fix_dist_;//TODO erase
	
	node["fix_k1"]>>calib_fix_k1_;
	node["fix_k2"]>>calib_fix_k2_;
	node["fix_k3"]>>calib_fix_k3_;
	node["fix_k4"]>>calib_fix_k4_;
	node["fix_k5"]>>calib_fix_k5_;
	node["fix_k6"]>>calib_fix_k6_;
	
	node["rational_model"]>>calib_rational_model_;
	node["termination_err"]>>termination_error_;
	node["max_count"]>>max_count_;
	node["count_criteria"]>>count_criteria_;
	node["eps_criteria"]>>eps_critera_;

	node["StereoName"]>>StereoName;
	node["outputDirectory"]>>outputDirectory;
	
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
	fs<<"compute_rectify_wDist"<<compute_rectify_wDist_;
	fs<<"debug_info"<<debugInfo_;
	fs<<"showIndiv"<<showIndividualMatches_;	
	fs<<"fix_intrinsic"<<calib_fix_intrinsic_;
	fs<<"guess_intrinsic"<<calib_guess_intrinsic_;
	fs<<"fix_principal"<<calib_fix_principal_;
	fs<<"fix_focal"<<calib_fix_focal_;
	fs<<"fix_aspect"<<calib_fix_aspect_;
	fs<<"same_focal"<<calib_same_focal_;
	fs<<"zero_tangent"<<calib_zero_tangent_;
	fs<<"fix_dist"<<calib_fix_dist_;
	fs<<"fix_k1"<<calib_fix_k1_;
	fs<<"fix_k2"<<calib_fix_k2_;
	fs<<"fix_k3"<<calib_fix_k3_;
	fs<<"fix_k4"<<calib_fix_k4_;
	fs<<"fix_k5"<<calib_fix_k5_;
	fs<<"fix_k6"<<calib_fix_k6_;
	
	fs<<"rational_model"<<calib_rational_model_;
	fs<<"termination_err"<<termination_error_;
	fs<<"max_count"<<max_count_;
	fs<<"count_criteria"<<count_criteria_;
	fs<<"eps_criteria"<<eps_critera_;

	fs<<"StereoName"<<StereoName;
	fs<<"outputDirectory"<<outputDirectory;

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

void StereoConfig::getMatchesOverlap(std::vector< std::vector< cv::Point2f > >& outLeft, std::vector< std::vector< cv::Point2f > >& outright,std::vector<int> &leftindex,std::vector<int> &rightindex)
{
	
	/**
	 * we can only use images in which the checkerboard pattern was found in both the left and right images...
	 * Thus the set of found images for each seperate camera must be compared against one another
	 * and only the where both are present, is the vector of points compared and added for the calibration*/
	std::vector< std::string > stripped_leftNames,stripped_rightNames;
	stripped_leftNames=removePrefixes(output_left_.indivNames);
	stripped_rightNames=removePrefixes(output_right_.indivNames);
	
	for(int lindex=0;lindex<stripped_leftNames.size();lindex++)
	{
		std::vector<std::string>::iterator foundIt=std::find(stripped_rightNames.begin(),stripped_rightNames.end(),stripped_leftNames.at(lindex));
		if(foundIt!=stripped_rightNames.end())
		{
			int integer_left,integer_right;//conversion from iterators to element numbers
			integer_left=lindex;
			integer_right=std::distance(stripped_rightNames.begin(),foundIt);
			
			//save to output vectors
			outLeft.push_back(output_left_.foundCorners.at(integer_left));
			leftindex.push_back(integer_left);
			
			outright.push_back(output_right_.foundCorners.at(integer_right));
			rightindex.push_back(integer_right);
			
		}
	}
	

}


std::vector< std::string > StereoConfig::removePrefixes(std::vector< std::string > input)
{
	/* removes all the prefixes in front of the image names up to the last underscore
	 * Note:: DataSet must adhere to these naming conventions */
	std::vector< std::string > Ans;
	for(int index=0;index<input.size();index++)
	{
		size_t found=input.at(index).find_last_of("_");
		std::string shortened=input.at(index);
		shortened.erase(shortened.begin(),shortened.begin()+found);
		Ans.push_back(shortened);
	}
	return Ans;
}

int StereoConfig::getCalibrationFlags()
{
		/*combines all the calibration flags into one single number to be 
	 * passed to opencv calibrate function*/
	int flags= 0;
	if(calib_fix_intrinsic_)
	{
		flags+=CV_CALIB_FIX_INTRINSIC;
	}
	if(calib_guess_intrinsic_)
	{
		flags+=CV_CALIB_USE_INTRINSIC_GUESS;
	}
	if(calib_fix_principal_)
	{
		flags+=CV_CALIB_FIX_PRINCIPAL_POINT;
	}
	if(calib_fix_focal_)
	{
		flags+=CV_CALIB_FIX_FOCAL_LENGTH;
	}
	if(calib_fix_aspect_)
	{
		flags+=CV_CALIB_FIX_ASPECT_RATIO;
	}
	if(calib_same_focal_)
	{
		flags+=CV_CALIB_SAME_FOCAL_LENGTH;
	}
	if(calib_zero_tangent_)
	{
		flags+=CV_CALIB_ZERO_TANGENT_DIST;
	}
	if(calib_fix_k1_)
	{
		flags+=CV_CALIB_FIX_K1;
	}
		if(calib_fix_k2_)
	{
		flags+=CV_CALIB_FIX_K2;
	}
		if(calib_fix_k3_)
	{
		flags+=CV_CALIB_FIX_K3;
	}
		if(calib_fix_k4_)
	{
		flags+=CV_CALIB_FIX_K4;
	}
		if(calib_fix_k5_)
	{
		flags+=CV_CALIB_FIX_K5;
	}
		if(calib_fix_k6_)
	{
		flags+=CV_CALIB_FIX_K6;
	}
	if(calib_rational_model_)
	{
		flags+=CV_CALIB_RATIONAL_MODEL;
	}
	
	return flags;
}

int StereoConfig::getTerminationFlags()
{
	int termination=0;
	if(count_criteria_)
	{
		termination+=cv::TermCriteria::COUNT;
	}
	if(eps_critera_)
	{
		termination+=cv::TermCriteria::EPS;
	}
	return termination;
}





	
	
}