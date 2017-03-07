#include "Calibration/StereoCalibrator.hpp"


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
	fs["leftcal"]>>left;
	fs.release();
	
	fs.open(rightxml,cv::FileStorage::READ);
	fs["rightcal"]>>right;
	fs.release();
	
	stereo::StereoConfig bumble_config;
	bumble_config.compute_left_=false;
	bumble_config.compute_right_=false;
	bumble_config.output_left_=left;
	bumble_config.output_right_=right;
	bumble_config.debugInfo_=false;
	bumble_config.compute_rectify_=false;
	bumble_config.showIndividualMatches_=true;
	bumble_config.calib_fix_intrinsic_=false;
	bumble_config.calib_guess_intrinsic_=false;
	bumble_config.calib_fix_principal_=false;
	bumble_config.calib_fix_focal_=false;
	bumble_config.calib_fix_aspect_=false;
	bumble_config.calib_same_focal_=true;
	bumble_config.calib_zero_tangent_=false;
	bumble_config.calib_fix_dist_=false;
	bumble_config.calib_rational_model_=false;
	
	bumble_config.termination_error_=1e-06;
	bumble_config.max_count_=2000;
	bumble_config.count_criteria_=true;
	bumble_config.eps_critera_=true;
	
	
	fs.open(outdir,cv::FileStorage::WRITE);
	fs<<"stereoconfig"<<bumble_config;
	fs.release();	
	
	
	//stereo::StereoCalibrator cal(leftxml,rightxml);
	
	//std::string indir(argv[1]);
	//SingleCalibrator currentCal(indir);
	//currentCal.configuration_.print();
	
	return 0;
}