
#include "DataStructures/DataSet/BumbleDataSet.hpp"
namespace stereo
{

BumbleDataSet::BumbleDataSet(std::string root)
{
	rootDir_=root;
	populateFrameList();
	current_frame_=frameReferences_.begin();
	++current_frame_;
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
	{		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if (boost::filesystem::is_regular_file(itr->path()))
		{
			files.push_back(itr->path().string());
		}
	}
	//sort into descending order
	std::sort(files.begin(),files.end());
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


cv::Mat BumbleDataSet::getCurrent()
{
	cv::Mat input,output;
	(*current_frame_).getBothImages(input);
	cv::cvtColor(input, output, cv::COLOR_BayerBG2RGB);
	cv::cvtColor(output, output, cv::COLOR_RGB2GRAY);
	std::cout<<(*current_frame_).Meta_.fileName_<<std::endl;
	return output;
}


cv::Mat BumbleDataSet::getCurrentLeft()
{
	cv::Mat input,output;
	(*current_frame_).getLeftImage(input);
	cv::cvtColor(input, output, cv::COLOR_BayerBG2RGB);
	//cv::cvtColor(output, output, cv::COLOR_RGB2GRAY);
	return output;
}

cv::Mat BumbleDataSet::getCurrentRight()
{
	cv::Mat input,output;
	(*current_frame_).getRightImage(input);
	cv::cvtColor(input, output, cv::COLOR_BayerBG2RGB);
	cv::cvtColor(output, output, cv::COLOR_RGB2GRAY);
	return output;
}


bool BumbleDataSet::decrementFrame()
{
	--current_frame_;
	if(current_frame_!=frameReferences_.begin())
	{
		return true;
	}
	else
	{
		++current_frame_;
		return false;
	}
}

bool BumbleDataSet::incrementFrame()
{

	++current_frame_;
	if(current_frame_!=frameReferences_.end())
	{
		return true;
	}
	else
	{
		--current_frame_;
		return false;
	}
}





/*	currentFrame_=ptrData_->frameReferences_.begin();
	cv::namedWindow( "Disp", cv::WINDOW_NORMAL );// Create a window for display.
	cv::namedWindow( "l", cv::WINDOW_NORMAL );// Create a window for display.
	cv::namedWindow( "R", cv::WINDOW_NORMAL );// Create a window for display.
	 
	while(currentFrame_!=ptrData_->frameReferences_.begin())
	{
		++currentFrame_;
		
		cv::Mat left,right,both;
		(*currentFrame_).getBothImages(both);
		(*currentFrame_).getLeftImage(left);
		(*currentFrame_).getRightImage(right);
		
		cv::imshow("Disp",both);
		cv::imshow("l",left);
		cv::imshow("R",right);
		cv::waitKey(delayTime);
	}
	
	cv::destroyWindow("Disp");*/





	
	
}