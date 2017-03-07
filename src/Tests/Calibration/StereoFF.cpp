#include "Calibration/StereoCalibrator.hpp"


int main(int argc,char* argv[])
{
	if((argc==2))
	{
		std::cout<<"Error!\nincorrect number of arguments, expects two directories to left and right xml outputs \n";
		std::cout<<"StereoCalibrateFromFile [Left.xml] [Right.xml]\n";
		return 1;
	}
	
	std::string in_xml(argv[1]);
	stereo::StereoCalibrator calib(in_xml);
	
	stereo::StereoOutput bumblebee_output;
	if(calib.calibrate(bumblebee_output))
	{
		
	}
	else
	{
		std::cout<<"error, failed to calibrate stereo camera correctly\n";
		return 1;
	}
	
	
	
//	std::cout<<calib.config_.compute_left_;
	//stereo::StereoCalibrator cal(leftxml,rightxml);
	
	//std::string indir(argv[1]);
	//SingleCalibrator currentCal(indir);
	//currentCal.configuration_.print();
	
	return 0;
}