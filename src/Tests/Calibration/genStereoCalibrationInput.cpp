#include "Calibration/StereoCalibrator.hpp"
/**
 * 
 * Generates a stereo configuration file at the specified directory
 * given the SingleOutput XML files of precalibrated cameras
 * i.e. assuming each camera is calibrated individually beforehand*/

int main(int argc,char* argv[])
{
	if(argc!=4)
	{
		std::cout<<"Error!\nincorrect number of arguments, expects two directories to left and right xml outputs\nAnd an output directory .xml\n";
		std::cout<<"StereoCalibrateFromFile [Left.xml] [Right.xml] [output.xml]\n";
		return 1;
	}
	
	std::string leftxml(argv[1]);
	std::string rightxml(argv[2]),outdir(argv[3]);
	
 	stereo::SingleOutput left,right;
	cv::FileStorage fs;
	fs.open(leftxml,cv::FileStorage::READ);
	fs["SingleOutput"]>>left;
	fs.release();
	
	fs.open(rightxml,cv::FileStorage::READ);
	fs["SingleOutput"]>>right;
	fs.release();
	
	stereo::StereoConfig bumble_config;
	bumble_config.compute_left_=false;
	bumble_config.compute_right_=false;
	bumble_config.output_left_=left;
	bumble_config.output_right_=right;
	bumble_config.debugInfo_=false;
	bumble_config.compute_rectify_wDist_=true;
	bumble_config.showIndividualMatches_=true;
	bumble_config.calib_fix_intrinsic_=false;
	bumble_config.calib_guess_intrinsic_=true;
	bumble_config.calib_fix_principal_=false;
	bumble_config.calib_fix_focal_=false;
	bumble_config.calib_fix_aspect_=false;
	bumble_config.calib_same_focal_=true;
	bumble_config.calib_zero_tangent_=false;
	bumble_config.calib_fix_dist_=false;//TODO erase
	bumble_config.calib_rational_model_=true;
	bumble_config.calib_fix_k1_=false;
	bumble_config.calib_fix_k2_=false;
	bumble_config.calib_fix_k3_=false;
	bumble_config.calib_fix_k4_=false;
	bumble_config.calib_fix_k5_=false;
	bumble_config.calib_fix_k6_=false;
	
	
	bumble_config.termination_error_=1e-06;
	bumble_config.max_count_=2000;
	bumble_config.count_criteria_=true;
	bumble_config.eps_critera_=true;
	

	bumble_config.StereoName="BumbleBeeConfig.xml";
	bumble_config.outputDirectory="/media/ubuntu/SD_CARD/ConfigurationFiles";
	
	
	fs.open(outdir,cv::FileStorage::WRITE);
	fs<<"stereoConfig"<<bumble_config;
	fs.release();	
	
	
	//stereo::StereoCalibrator cal(leftxml,rightxml);
	
	//std::string indir(argv[1]);
	//SingleCalibrator currentCal(indir);
	//currentCal.configuration_.print();
	
	return 0;
}