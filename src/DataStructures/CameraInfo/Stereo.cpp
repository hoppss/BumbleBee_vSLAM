#include "DataStructures/CameraInfo/Stereo.hpp"

namespace stereo
{

Stereo::Stereo()
{
	toPixel.setIdentity();
}

Stereo::~Stereo()
{
	
}


/*
cv::Mat StereoInfo::generateIdealP(cv::Mat k, isotransform::Isometry input)
{
	cv::Mat Ans;
	Ans=cv::Mat::zeros(3,4,CV_64FC1);

	Ans.at<double>(0,3)=	input.getT().at<double>(0,0);
	Ans.at<double>(1,3)=input.getT().at<double>(1,0);
	Ans.at<double>(2,3)=input.getT().at<double>(2,0);
	//set the translation

	Ans.at<double>(0,0)=1;
	Ans.at<double>(1,1)=1;
	Ans.at<double>(2,2)=1;
	//set Identity
	
	//	[ 1 0 0 | t1 ]
	//  [ 0 1 0 | t2 ]
	//	[ 0 0 1 | t3 ]
	//
	Ans=input.getR()*Ans;

	
	Ans=k*Ans;

	return Ans;
}


*/




//set methods


void Stereo::setCameraInfo(bool left, cv::Mat k, cv::Mat dist,Isometry iso)
{
	if(left)
	{
		cam_left_.setData(k,dist,iso);
	}
	else
	{
		cam_right_.setData(k,dist,iso);
	}
}


void Stereo::setCalibImgSize(cv::Size calib)
{
	cal_size_=calib;
}

void Stereo::setPixel(Isometry pix)
{
	toPixel=pix;
}



//Output

void Stereo::printConfig(CoordinateSystem sys)
{
	
	std::cout<<"Stereo Camera Configuration"<<std::endl;
	std::cout<<"________________________________"<<std::endl;
	switch(sys)
	{
		case LeftCamera:
		{
			std::cout<<"Left Camera Coordinate System"<<std::endl;
			break;
		}
		case LeftPixel:
		{
			std::cout<<"left Pixel Coordinate System"<<std::endl;
			break;
		}
	}
	std::cout<<"{Left Camera}"<<std::endl;
	cam_left_.printInternals();
	std::cout<<"{Right Camera}"<<std::endl;
	cam_right_.printInternals();
	std::cout<<"{BaseLine}"<<std::endl;
	getBaseline(sys).printH();
	std::cout<<"{Essential Matrix}"<<getEssentialMatrix(sys) <<std::endl;
	std::cout<<"{Fundamental Matrix}"<<getFundamentalMatrix(sys)<<std::endl;
	std::cout<<"{Image Calibration Size}  :   "<<cal_size_<<std::endl;
	std::cout<<"________________________________"<<std::endl;
}

cv::Mat Stereo::getEssentialMatrix(Stereo::CoordinateSystem sys)
{
	Isometry baseline;
	
	baseline=getBaseline(sys);

	cv::Mat Ans=stereo::getCrossProductMatrix(baseline.getT())*baseline.getR();
	
	return Ans;

}

cv::Mat Stereo::getFundamentalMatrix(Stereo::CoordinateSystem sys)
{
	cv::Mat essent;
	essent=getEssentialMatrix(sys);
	
	cv::Mat inv_trans_r_cam;
	
	
	cv::transpose(cam_right_.K_.inv(),inv_trans_r_cam);
	
	cv::Mat Ans=inv_trans_r_cam*essent*cam_left_.K_.inv();
	
	return Ans;
}





/*
cv::Mat StereoInfo::getEssentialMatrix()
{
	
	cv::Mat Ans,tx;
	tx=cv::Mat::zeros(3,3,CV_64FC1);
	tx.at<double>(1,0)=baseline_.getT().at<double>(2,0);
	tx.at<double>(2,0)=-baseline_.getT().at<double>(1,0);
	tx.at<double>(2,1)=baseline_.getT().at<double>(0,0);

	tx.at<double>(0,1)=-baseline_.getT().at<double>(2,0);
	tx.at<double>(0,2)=baseline_.getT().at<double>(1,0);
	tx.at<double>(1,2)=-baseline_.getT().at<double>(0,0);	
	
	Ans=tx*baseline_.getR();
	
	
	return Ans;
}


*/

/*
 * Baseline is defined as coordinate system change from left to right camera system
 * 
 * 
 *									|--->(camera_left_iso)----->|(LEFTCAMERA FRAME) 
 * (CENTRE OF MASS)|
 *									|--->(camera_right_iso)----->|(RightTCAMERA FRAME) 
 * 
 * 
 * Baseline
 * 
 * (CAMERA LEFT) -----> BaseLine----> (CAMERA RIGHT)
 * 
 * 
 * */

Isometry Stereo::getBaseline(CoordinateSystem sys)
{
	Isometry Ans;
	Ans.setIdentity();
	switch(sys)
	{
		case LeftCamera :
		{
			//baseline is right camera to the left coordinate frame 
			Ans=cam_left_.iso_.invert()*cam_right_.iso_;
			break;
		}
		case LeftPixel :
		{
			Ans=cam_left_.iso_.invert()*cam_right_.iso_;
			//Ans=(toPixel.invert())*(cam_left_.iso_.invert())*cam_right_.iso_*toPixel;
			break;
		}
	}
	
	//get inverse since we need the baseline specified in terms of point system transform as opposed to coordinate system transform

	Ans.invertThis();
	
	return Ans;
	
}


void Stereo::read(const cv::FileNode& node)
{
	std::string tempf;

	node["left_camera"]>>cam_left_;
	node["right_camera"]>>cam_right_;
	node["calibration_size"]>>cal_size_;
	node["to_p"]>>toPixel;
}


void Stereo::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"left_camera"<<cam_left_;
	fs<<"right_camera"<<cam_right_;
	fs<<"calibration_size"<<cal_size_;
	fs<<"to_p"<<toPixel;
	fs<<"}";

}





}