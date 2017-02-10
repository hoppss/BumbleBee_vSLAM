#include "DataStructures/Transforms/Isometry.hpp"


namespace stereo{
	
	
cv::Mat eulerMat(double roll, double pitch, double yaw, bool radians)
{
	cv::Mat r_x,r_y,r_z;
	double roll_rad,pitch_rad,yaw_rad;
	if(radians)
	{
		roll_rad=roll;
		pitch_rad=pitch;
		yaw_rad=yaw;
	}
	else
	{
		roll_rad=(roll*M_PI)/180.0;
		pitch_rad=(pitch*M_PI)/180.0;
		yaw_rad=(yaw*M_PI)/180.0;
	}
	
	r_x= (cv::Mat_<double>(3,3) <<
               1,       0,              0,
               0,       cos(roll_rad),   -sin(roll_rad),
               0,       sin(roll_rad),   cos(roll_rad)
               );
	r_y= (cv::Mat_<double>(3,3) <<
               cos(pitch_rad),    0,      sin(pitch_rad),
               0,               1,      0,
               -sin(pitch_rad),   0,      cos(pitch_rad)
               );
	
	r_z=(cv::Mat_<double>(3,3) <<
               cos(yaw_rad),    -sin(yaw_rad),      0,
               sin(yaw_rad),    cos(yaw_rad),       0,
               0,               0,                  1);
	
	cv::Mat Ans= r_z*r_y*r_x;
	return Ans;
	
}

cv::Mat getCrossProductMatrix(cv::Mat vec)
{
	
	//(a,b,c)|| (a,
	//					 b,
	//					 c)	
	//
	//
	cv::Mat Ans;
	Ans=cv::Mat::zeros(3,3,CV_64FC1);
	
	if( (vec.size().width==1)&&(vec.size().height==3)) //column vector
	{
			Ans.at<double>(0,1)=-1*vec.at<double>(2,0);//-a3
			Ans.at<double>(0,2)=vec.at<double>(1,0);//a2
			Ans.at<double>(1,2)	=-1*vec.at<double>(0,0);//-a1
			Ans.at<double>(1,0)	=vec.at<double>(2,0);//a3
			Ans.at<double>(2,0)	=-1*vec.at<double>(1,0);//-a2
			Ans.at<double>(2,1)	=vec.at<double>(0,0);//a1
		
	}
	else
	{
		if( (vec.size().width==3)&&(vec.size().height==1))//row vector
		{
			
			Ans.at<double>(0,1)=-1*vec.at<double>(0,2);//-a3
			Ans.at<double>(0,2)=vec.at<double>(0,1);//a2
			Ans.at<double>(1,2)	=-1*vec.at<double>(0,0);//-a1
			Ans.at<double>(1,0)	=vec.at<double>(0,2);//a3
			Ans.at<double>(2,0)	=-1*vec.at<double>(0,1);//-a2
			Ans.at<double>(2,1)	=vec.at<double>(0,0);//a1
		}
	}
	return Ans;
	
}

cv::Mat Isometry::getR()
{
	return rot_;
}

cv::Mat Isometry::getT()
{
	return trans_;
}


	
  
Isometry::Isometry()
{
	init_map();
}

Isometry::Isometry(cv::Mat H)
{
	init_map();
	setH(H);
}

Isometry::Isometry(cv::Mat R, cv::Mat T)
{
	init_map();
	setRT(R,T);
}

void Isometry::printH()
{
	std::cout<<"H - "<<std::endl<<H_<<std::endl;
	std::cout<<"R - "<<std::endl<<rot_<<std::endl;
	std::cout<<"T - "<<std::endl<<trans_<<std::endl;
}

void Isometry::setIdentity()
{
	H_=cv::Mat::zeros(4,4,CV_64FC1);
	H_.at<double>(3,3)=1.0;	
	rot_=cv::Mat::eye(3,3,CV_64FC1);
}

void Isometry::init_map()
{
	H_=cv::Mat(4,4,CV_64FC1);
	trans_=H_(cv::Rect(3,0,1,3));
	rot_=H_(cv::Rect(0,0,3,3));
}

Isometry Isometry::invert()
{
	Isometry Ans(this->H_.inv());
	return Ans;
}

void Isometry::invertThis()
{
	H_=H_.inv();
}


void Isometry::setH(cv::Mat H)
{
	H.copyTo(H_);
}

void Isometry::setRT(cv::Mat R, cv::Mat T)
{
	H_.at<double>(3,0)=0.0;
	H_.at<double>(3,1)=0.0;
	H_.at<double>(3,2)=0.0;
	H_.at<double>(3,3)=1.0;
	
	R.copyTo(rot_);
	T.copyTo(trans_);
}


void Isometry::setIso(Isometry new_iso)
{
	setH(new_iso.H_);
}





//-------------------------
//operator overloads
//----------------------

Isometry& Isometry::operator=(const Isometry& rhs)
{
	rhs.H_.copyTo(this->H_);	
	return *this;
}

Isometry Isometry::operator*(const Isometry& rhs)
{
	cv::Mat new_homog;
	new_homog=(this->H_)*rhs.H_;
	Isometry Ans(new_homog);
	
	//ptr_&=Ans;
	
	return Ans;	
}

Isometry& Isometry::operator*=(const Isometry& rhs)
{
	cv::Mat new_homog;
	new_homog=(this->H_)*rhs.H_;
	new_homog.copyTo(this->H_);
	return *this;
}



//read and write functions from xml

void Isometry::read(const cv::FileNode& node)
{
	cv::Mat rr,tt;
	node["R"]>>rr;
	node["T"]>>tt;
	setRT(rr,tt);
}

void Isometry::write(cv::FileStorage& fs) const
{
	fs<<"{";
	fs<<"R"<<rot_;
	fs<<"T"<<trans_;
	fs<<"}";
}

};



