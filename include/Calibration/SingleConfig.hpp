#ifndef SINGLE_CONFIGURATION_HEADER_HPP_
#define SINGLE_CONFIGURATION_HEADER_HPP_

#include <iostream>
#include <bitset>

#include <opencv2/core.hpp>
#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <cstdlib>

namespace stereo
{
class SingleConfig{
	private:
	public:
		enum calUnits
		{
			m=0,
		  cm=1,
			mm=2
		};
		std::string filename;
		std::string in_directory;
		std::string out_directory;
		int patternRow;
		int patternCol;
		int squareSize;
		bool debugInfo;
		bool saveFound;
		bool saveNotFound;
		calUnits unit;
		void write(cv::FileStorage& fs) const;
		void read(const cv::FileNode& node);
		void print();
		SingleConfig();

};

//These write and read functions must be defined for the serialization in FileStorage to work

static void read(const cv::FileNode& node, stereo::SingleConfig& x, const stereo::SingleConfig& default_value = stereo::SingleConfig()){
    if(node.empty())
	{
        x = default_value;
	}
    else
	{
        x.read(node);
	}
}

static void write(cv::FileStorage& fs, const std::string&, const stereo::SingleConfig& x)
{
    x.write(fs);
}



	
}


#endif