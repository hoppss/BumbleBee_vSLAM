#include "Calibration/StereoCalibrator.hpp"

/*expects a stereo configuration file, from which the calibration will be executed
 * for the bumblee bee camera, and stored into a stereo object */

int main(int argc,char* argv[])
{
	if((argc!=2))
	{
		std::cout<<"Error!\nincorrect number of arguments, expects a single stereo configuration file \n";
		std::cout<<"StereoFromFile [stereo.xml]\n";
		return 1;
	}
	
	std::string in_xml(argv[1]);
	stereo::StereoCalibrator calib(in_xml);
	
	stereo::Stereo bumblebee_output;
	if(calib.calibrate(bumblebee_output))
	{
	
		std::cout<<"Sequence Completed Successfully";
		
	}
	else
	{
		std::cout<<"error, failed to calibrate stereo camera correctly\n";
		return 1;
	}
	return 0;
}