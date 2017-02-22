#include "Calibration/SingleCalibrator.hpp"
#include <bitset>

int main(int argc, char * argv[])
{
	using namespace stereo;
	if(argc!=2)
	{
		std::cout<<"Error!\nincorrect number of arguments, expects a single directory to a configuration file xml\n";
		std::cout<<"SingleCalibrateFromFile [directoryName.xml]\n";
		return 1;
	}
	std::string indir(argv[1]);
	SingleCalibrator currentCal(indir);
	currentCal.configuration_.print();

	
	SingleOutput ans;
	currentCal.calibrate(ans);
	
	SingleOutput m;

	
	cv::FileStorage rr("/media/ubuntu/SD_CARD/calibration/out/leftcal.xml",cv::FileStorage::READ);
	rr["leftcal"]>>m;
	rr.release();
/*

	

	SingleOutput left;
	
	left.setMetaData(pref,out,deb);
	
	int debugConf=SingleOutput::debugInfo;
	
	std::cout<<"debug info- "<<std::bitset<6>(debugConf)<<std::endl;
	left.calibrateCamera(in,outfold,patternsize_rows,patternsize_cols,squareSize,un,debugConf);

	*/
	
	return 0;
}

