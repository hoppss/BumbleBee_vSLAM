#include "Calibration/StereoOutput.hpp"

void printExpectedArgs();

int main(int argc, char * argv[])
{
	
	using namespace stereo;
	
	/**
	 * Manually setting files for now
	 * */
/*	std::string left="/media/ubuntu/SD_CARD/calibration/left";
	std::string right="/media/ubuntu/SD_CARD/calibration/right";
	std::string outfold="/media/ubuntu/SD_CARD/calibration";
	std::string  out="output";
	std::string deb="debug";
	std::string pref="left_";
	bool fullDebug=true;
	int patternsize_rows=12;
	int patternsize_cols=10;
	int squareSize=37;
	int un=SingleOutput::mm;
	
	///calibrate left
	
	SingleOutput lc,rc;
	
	lc.setMetaData(pref,out,deb);
	int debugConf=SingleOutput::debugInfo|SingleOutput::saveFound|SingleOutput::saveNotFound;
	lc.calibrateCamera(left,outfold,patternsize_rows,patternsize_cols,squareSize,un,debugConf);
	
	//calibrate right
	pref="right_";
	rc.setMetaData(pref,out,deb);
	rc.calibrateCamera(right,outfold,patternsize_rows,patternsize_cols,squareSize,un,debugConf);

	//estimate baseline
	
	StereoOutput ster;
	ster.calibrateStereo(lc,rc);
	
	*/
	return 0;
}

void printExpectedArgs()
{
	std::cout<<"ERROR!!---expected arguments as follows\n";
	std::cout<<"calibrateFromFile [inputDirectory] [outputDirectory] [debug-true or false] [n_rows] [n_cols] [square size]\n";
}
