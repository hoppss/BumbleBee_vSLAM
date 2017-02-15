#ifndef ISOTRANSFORM_ISOMETRY_HEADER_HPP_
#define ISOTRANSFORM_ISOMETRY_HEADER_HPP_
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace stereo
{
cv::Mat eulerMat(double roll,double pitch,double yaw,bool radians);
cv::Mat getCrossProductMatrix(cv::Mat vec);
	
class Isometry{
  private:
    cv::Mat rot_,trans_;
    cv::Mat H_;
	void init_map();
  public:
    Isometry();
    Isometry(cv::Mat R,cv::Mat T);
    Isometry(cv::Mat H);
	void setIdentity();
	void setRT(cv::Mat R,cv::Mat T);
	void setH(cv::Mat H);
	void setIso(Isometry new_iso);
	cv::Mat getR();
	cv::Mat getT();
	Isometry invert();
	void invertThis();
	void printH();
	Isometry& operator = (const Isometry& rhs);
	Isometry& operator *= (const Isometry& rhs);
	Isometry operator * (const Isometry& rhs);  //Return a copy of the incremented Isometry, not modify internals
	//read and write functions from xml
	void write(cv::FileStorage& fs) const;
	void read(const cv::FileNode& node);	
  protected:
};
//These write and read functions must be defined for the serialization in FileStorage to work

static void read(const cv::FileNode& node, stereo::Isometry& x, const stereo::Isometry& default_value = stereo::Isometry()){
    if(node.empty())
	{
        x = default_value;
				x.setIdentity();
	}
    else
	{
        x.read(node);
	}
}

static void write(cv::FileStorage& fs, const std::string&, const stereo::Isometry& x)
{
    x.write(fs);
}


}




#endif
