#include "Calibration/Calibrator.hpp"
#include <bitset>

void printExpectedArgs();

int main(int argc, char * argv[])
{
	
	/*
	 * Note : This assumes directories are already in place,
	 * i.e if the input and output directories dont exist for the images, they wont be created
	 * and thus nothing will be saved
	 * */
	using namespace stereo;
	Calibrator cal;
	Single l_,r_;
	
	//setup configuration
	//assuming full debug must be produced
	if(argc!=7)
	{
		printExpectedArgs();
		return 1;
	}
	
	std::string in(argv[1]);
	std::string  out(argv[2]);
	std::stringstream temp(argv[3]);
	int patternsize_rows=atoi(argv[4]);
	int patternsize_cols=atoi(argv[5]);
	int squareSize=atoi(argv[6]);;
	
	bool debug;
	
	temp>>std::boolalpha>>debug;

	
	int config;
	
	config=(saveFoundBoards|debugLeft|debugRight);
		
	std::cout<<"config --\n";
	std::cout<<"input directory - "<<in<<std::endl;
	std::cout<<"output directory - "<<out<<std::endl;
	std::cout<<"debug info- "<<std::bitset<8>(config)<<std::endl;
	
	//calibrate the left camera
	std::string fullcam_dir;
	std::string fulloutput_dir;
	
	fullcam_dir=in;
	fullcam_dir+="/left";
	
	fulloutput_dir=out;
	fulloutput_dir+="/left";

	l_=cal.calibrateCamera(fullcam_dir,config,fulloutput_dir,patternsize_rows,patternsize_cols,squareSize);

	//calibrate the right camera
	fullcam_dir=in;
	fullcam_dir+="/right";
	
	fulloutput_dir=out;
	fulloutput_dir+="/right";
	
	r_=cal.calibrateCamera(fullcam_dir,config,fulloutput_dir,patternsize_rows,patternsize_cols,squareSize);

	
	
	
	
	
	
	return 0;
}

void printExpectedArgs()
{
	std::cout<<"ERROR!!---expected arguments as follows\n";
	std::cout<<"calibrateFromFile [inputDirectory] [outputDirectory] [debug-true or false] [n_rows] [n_cols] [square size]\n";
}
