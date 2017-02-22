#include "Calibration/SingleOutput.hpp"
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
	SingleConfig info;

	cv::FileStorage fs(std::string(argv[1]),cv::FileStorage::READ);
	fs["configuration"]>>info;
	fs.release();
	
	
	info.print();
/*	SingleConfig debug;
	debug.filename="leftcal";
	debug.in_directory="/media/ubuntu/SD_CARD/calibration/left";
	debug.out_directory="/media/ubuntu/SD_CARD/calibration";
	debug.patternCol=10;
	debug.patternRow=12;
	debug.squareSize=37;
	debug.debugInfo=true;
	debug.saveFound=true;
	debug.saveNotFound=false;
	debug.unit=SingleConfig::mm;
	*/
	
//	cv::FileStorage f("/media/ubuntu/SD_CARD/calibration/in.xml",cv::FileStorage::WRITE);
//	f<<"configuration"<<debug;
//	f.release();
	/*
	cv::FileStorage fsa("/media/ubuntu/SD_CARD/calibration/in.xml",cv::FileStorage::READ);
	
	SingleConfig a;
	fsa["configuration"]>>a;
	
	std::cout<<a.filename;
	fsa.release();*/
/*	std::string in="/media/ubuntu/SD_CARD/calibration/right";
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

	*/
	
	return 0;
}

