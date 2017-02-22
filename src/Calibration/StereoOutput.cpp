#include "Calibration/StereoOutput.hpp"
namespace stereo
{
	
	
StereoOutput::StereoOutput()
	{
		
	}
	
/*
bool StereoOutput::calibrateStereo(SingleOutput& left, SingleOutput& right)
{
	bool Ans;
	cv::TermCriteria crit;
	crit.epsilon=0.2;
	crit.maxCount=3000;
	crit.type=cv::TermCriteria::COUNT+cv::TermCriteria::EPS;
	
	std::vector< std::vector< cv::Vec3f > > combined[2];
	combined[0]=left.generateCheckBoardCoord();
	combined[1]=right.generateCheckBoardCoord();

		std::cout<<"Trying"<<std::endl;
	cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS,80,pow(1.0,-6));
	
	
	// Note, we are assuming the left and right images are the same
	// i.e. any images where no checkerboard was found has been removed in both the left and right image directories
	
	meas_error=cv::stereoCalibrate(getChessPoints(left.internalBoardSize,left.size_square,left.outputImages.size()),
											left.foundCorners,right.foundCorners,
											left.measured_k,left.measured_d,
										  right.measured_k,right.measured_d,
										  left.calibration_size,
										  baseline_R_,baseline_T_,essential_,fundamental_,
											cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS,400,pow(1.0,-6)),
											CV_CALIB_FIX_INTRINSIC);
 									//			);
									//		crit,
									//		CV_CALIB_FIX_INTRINSIC);
 										//		);//,
										//	cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS,80,0.0005),cv::CV_CALIB_FIX_INTRINSIC);

	std::cout<<meas_error<<"    rms"<<std::endl;
	
	std::cout<<baseline_T_;
	std::cout<<baseline_R_;
	
	
	return Ans;
}

std::vector< std::vector< cv::Point3f > > StereoOutput::getChessPoints(cv::Size board, double square_size, int n)
{
	
	std::vector< std::vector< cv::Point3f > > Ans;
	
	for(int pattern=0;pattern<n;pattern++)
	{
		std::vector< cv::Point3f > singleBoard;
		for(int row=0;row<board.height;row++)
		{
			for(int col=0;col<board.width;col++)
			{
				cv::Point3f tempPoint;
				tempPoint.x=col*square_size;
				tempPoint.y=row*square_size;
				tempPoint.z=0;
				singleBoard.push_back(tempPoint);
			}
		}
		Ans.push_back(singleBoard);
	}
	return Ans;
}


void StereoOutput::saveConfiguration(std::string dir, bool lean,SingleOutput& left, SingleOutput& right)
{
	Single leftcamera,rightcamera;
	leftcamera=left.generateSingle();
	rightcamera=right.generateSingle();
	
	if(lean)
	{

	}
	else
	{
	}
}

*/
	
	
	
}