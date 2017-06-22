
#include "DataStructures/DataSet/BumbleDataSet.hpp"
namespace stereo
{

BumbleDataSet::BumbleDataSet(std::string root)
{
	rootDir_=root;
	populateFrameList();
}

std::vector< std::string > BumbleDataSet::getFilesList(std::string dir)
{
	//search through a directory, and populate a vector of string filenames, return a copy of the vector
	boost::filesystem::directory_iterator end_itr,itr(dir);
	std::vector<std::string> files;
	for (itr; itr != end_itr; ++itr)
  {
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
    if (boost::filesystem::is_regular_file(itr->path()))
		{
			boost::filesystem::path tempPath(itr->path().string());
			files.push_back(tempPath.filename().string());
		}
	}
	return files;
}

std::vector< std::string > BumbleDataSet::getDirList(std::string dir)
{
	//search through a directory, and populate a vector of string filenames, return a copy of the vector
	boost::filesystem::directory_iterator end_itr,itr(dir);
	std::vector<std::string> files;
	for (itr; itr != end_itr; ++itr)
  {
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
    if (boost::filesystem::is_regular_file(itr->path()))
		{

			files.push_back(itr->path().string());
		}
	}
	return files;
}



void BumbleDataSet::populateFrameList()
{
	std::vector<std::string> ImageFiles;
	// cycle through the left camera + right camera directory

	ImageFiles=getDirList(rootDir_);
	//add left and right images to frame object + push to queue
	std::vector<std::string>::iterator endit=ImageFiles.end();
	
	
	for(std::vector<std::string>::iterator it=ImageFiles.begin();it!=endit;++it)
	{
			BumbleFrame newFrame;
			newFrame.Meta_.fullDir_=*it;
			boost::filesystem::path Name(newFrame.Meta_.fullDir_);
			newFrame.Meta_.fileName_=Name.filename().string();
			frameReferences_.push_back(newFrame);
	}

}

void BumbleDataSet::playback()
{
	currentFrame_=frameReferences_.begin();
  cv::namedWindow( "Disp", cv::WINDOW_NORMAL );// Create a window for display.
	 cv::namedWindow( "l", cv::WINDOW_NORMAL );// Create a window for display.
	  cv::namedWindow( "R", cv::WINDOW_NORMAL );// Create a window for display.
	 
	while(currentFrame_!=frameReferences_.end())
	{
		++currentFrame_;
		
		cv::Mat left,right,both;
		(*currentFrame_).getBothImages(both);
		(*currentFrame_).getLeftImage(left);
		(*currentFrame_).getRightImage(right);
		
	//	cv::Mat leftImg=cv::imread((*currentFrame_).Meta_.fullDir_, CV_LOAD_IMAGE_GRAYSCALE);
		cv::imshow("Disp",both);
		cv::imshow("l",left);
		cv::imshow("R",right);
		cv::waitKey(50);
	}
	
	cv::destroyWindow("Disp");
	
}



	
	
}