#include "Calibration/StereoCalibrator.hpp"


int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		std::cout<<"Error!\nincorrect number of arguments, expects two directories to left and right xml outputs \n";
		std::cout<<"StereoCalibrateFromFile [Left.xml] [Right.xml]\n";
		return 1;
	}
	
	std::string leftxml(argv[1]),rightxml(argv[2]);
	
	stereo::StereoCalibrator cal(leftxml,rightxml);
	
	//std::string indir(argv[1]);
	//SingleCalibrator currentCal(indir);
	//currentCal.configuration_.print();
	
	return 0;
}