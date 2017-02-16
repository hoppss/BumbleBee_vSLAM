#include "Calibration/SingleOutput.hpp"
#include <bitset>

int main(int argc, char * argv[])
{
	using namespace stereo;
	std::string in="/media/ubuntu/SD_CARD/calibration/right";
	std::string outfold="/media/ubuntu/SD_CARD/calibration";
	std::string  out="output";
	std::string deb="debug";
	std::string pref="file_";
	bool fullDebug=true;
	int patternsize_rows=12;
	int patternsize_cols=10;
	int squareSize=37;
	int un=SingleOutput::mm;
	

	SingleOutput left;
	
	left.setMetaData(pref,out,deb);
	
	int debugConf=SingleOutput::debugInfo;
	
	std::cout<<"debug info- "<<std::bitset<6>(debugConf)<<std::endl;
	left.calibrateCamera(in,outfold,patternsize_rows,patternsize_cols,squareSize,un,debugConf);

	
	
	return 0;
}

