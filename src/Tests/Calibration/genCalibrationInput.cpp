#include "Calibration/SingleConfig.hpp"

int main(int argc, char * argv[])
{
	using namespace stereo;
	/*Creates the single camera calibration configuration file
	 * to be used for both the left and right bumblebee Cameras.
	 * Must be edited or the xml file directly modified if the directories
	 * of each set of images is moved*/
	
	if(argc!=3)
	{
		std::cout<<"Error!\nincorrect number of arguments, expects a single directory to an output configuration file xml\n";
		std::cout<<"genCalibrationInput [directoryName.xml]\n";
		return 1;
	}
	
	SingleConfig debug;
	debug.filename="leftcal";
	debug.in_directory="/media/ubuntu/SD_CARD/calibration/left";
	debug.out_directory="/media/ubuntu/SD_CARD/calibration/leftOutput";
	debug.patternCol=10;
	debug.patternRow=12;
	debug.squareSize=37;
	debug.debugInfo=true;
	debug.saveFound=true;
	debug.saveNotFound=false;
	debug.unit=SingleConfig::mm;
	debug.robustCheckerBoard=true;
	debug.saveDrawn=true;
	debug.displayFound=false;
	debug.displayNotFound=false;
	debug.cal_adaptive=true;
	debug.cal_filter=true;
	debug.cal_normalize=false;
	debug.compute_rational_model=true;
	debug.displayMapping=false;
	debug.displayUndistorted=false;

	cv::FileStorage fs_l(std::string(argv[1]),cv::FileStorage::WRITE);
	fs_l<<"SingleConfig"<<debug;
	fs_l.release();
	
	SingleConfig Rightdebug;
	Rightdebug.filename="rightcal";
	Rightdebug.in_directory="/media/ubuntu/SD_CARD/calibration/right";
	Rightdebug.out_directory="/media/ubuntu/SD_CARD/calibration/rightOutput";
	Rightdebug.patternCol=10;
	Rightdebug.patternRow=12;
	Rightdebug.squareSize=37;
	Rightdebug.debugInfo=true;
	Rightdebug.saveFound=true;
	Rightdebug.saveNotFound=false;
	Rightdebug.unit=SingleConfig::mm;
	Rightdebug.robustCheckerBoard=true;
	Rightdebug.saveDrawn=true;
	Rightdebug.displayFound=false;
	Rightdebug.displayNotFound=false;
	Rightdebug.cal_adaptive=true;
	Rightdebug.cal_filter=true;
	Rightdebug.cal_normalize=false;
	Rightdebug.compute_rational_model=true;
	Rightdebug.displayMapping=false;
	Rightdebug.displayUndistorted=false;

	cv::FileStorage fs_r(std::string(argv[2]),cv::FileStorage::WRITE);
	fs_r<<"SingleConfig"<<Rightdebug;
	fs_r.release();

	
	return 0;
}

