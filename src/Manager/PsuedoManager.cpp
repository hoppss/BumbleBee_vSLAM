#include "Manager/PsuedoManager.hpp"

namespace stereo 
{

PsuedoManager::PsuedoManager(std::string rootDir)
{
	rootDir_=rootDir;
	leftDir_=rootDir_+"/data/left";
	rightDir_=rootDir_+"/data/right";
	populateFrameList();
}

//utilities

std::vector< std::string > PsuedoManager::getFilesList(std::string dir)
{
	boost::filesystem::directory_iterator end_itr,itr(dir);
	std::vector<std::string> files;
	for (itr; itr != end_itr; ++itr)
  {
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
    if (boost::filesystem::is_regular_file(itr->path()))
		{
			boost::filesystem::path tempPath(itr->path().string());
			
			std::cout<<tempPath.filename()<<std::endl;
			files.push_back(itr->path().string());
			//--std::cout<<itr->path().string()<<std::endl;
		}
	}
	
	return files;
}





void PsuedoManager::populateFrameList()
{
	std::vector<std::string> leftFiles,rightFiles;
	// cycle through the left camera + right camera directory
	leftFiles=getFilesList(leftDir_);
	rightFiles=getFilesList(rightDir_);
	
}



/*
using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    // list all files in current directory.
    //You could put any file path in here, e.g. "/home/me/mwah" to list that directory
    path p (".");

    directory_iterator end_itr;

    // cycle through the directory
    for (directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            string current_file = itr->path().string();
            cout << current_file << endl;
        }
    }
}
*/



}