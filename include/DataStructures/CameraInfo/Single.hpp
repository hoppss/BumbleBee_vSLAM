   #ifndef CAMERA_INFO_SINGLE_HEADER_HPP
#define CAMERA_INFO_SINGLE_HEADER_HPP

#include "DataStructures/Transforms/Isometry.hpp"
namespace stereo {

class Single
{
	private:
		Isometry  iso_;//Coordinate Transform from world to camera
		/*
		 * 		(WORLD SYSTEM)--->iso_----->(Camera Coordinate System)
		 * 
		 * 		there Xcam=(iso_^-1)Xworld
		 * */
		cv::Mat K_,K_dist_;
		cv::Mat undistort_map_;
		void setData(cv::Mat k,cv::Mat dist,Isometry is);
	public:
		Single();
		~Single();
		Single(cv::Mat k,cv::Mat dist,Isometry is);
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
		double RMS_Error;
		void printInternals();
		//TODO gen ideal P

	protected:
				friend class StereoCalibrator;
				friend class Stereo;

};

//These write and read functions must be defined for the serialization in FileStorage to work

static void read(const cv::FileNode& node, stereo::Single& x, const stereo::Single& default_value = stereo::Single()){
    if(node.empty())
	{
        x = default_value;
	}
    else
	{
        x.read(node);
	}
}

static void write(cv::FileStorage& fs, const std::string&, const stereo::Single& x)
{
    x.write(fs);
}





}

#endif