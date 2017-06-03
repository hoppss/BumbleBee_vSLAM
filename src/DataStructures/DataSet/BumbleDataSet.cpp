
#include "DataStructures/DataSet/BumbleDataSet.hpp"
namespace stereo
{

BumbleDataSet::BumbleDataSet(std::string root)
{
	rootDir_=root;
	leftDir_=rootDir_+"/data/left";
	rightDir_=rootDir_+"/data/right";
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
	std::vector<std::string> leftDirect;
	// cycle through the left camera + right camera directory

	leftDirect=getDirList(leftDir_);
	//add left and right images to frame object + push to queue
	std::vector<std::string>::iterator endit=leftDirect.end();
	
	
	for(std::vector<std::string>::iterator it=leftDirect.begin();it!=endit;++it)
	{
			BumbleFrame newFrame;
			newFrame.leftMeta_.fullDir_=*it;
			boost::filesystem::path leftName(newFrame.leftMeta_.fullDir_);
			newFrame.leftMeta_.fileName_=leftName.filename().string();
			
			newFrame.rightMeta_.fileName_=newFrame.leftMeta_.fileName_+"/"+leftName.filename().string();
			newFrame.rightMeta_.fileName_=rightDir_+"/"+newFrame.leftMeta_.fileName_;

			frameReferences_.push_back(newFrame);
	}
	
	//sort in ascending order
	std::sort(frameReferences_.begin(),frameReferences_.end(), [ ]( const BumbleFrame& lhs, const BumbleFrame& rhs )
	{
		return lhs.leftMeta_.getTimeStamp() < rhs.leftMeta_.getTimeStamp();
	});
	
}


	
	
}