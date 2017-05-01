#include "Manager/OutputSettings.hpp"

namespace stereo {

OutputSettings::OutputSettings()
{
		//set the default settings if nothing else is loaded
		root_out_dir_=DEFAULT_ROOT_OUT_;
		root_in_dir_=DEFAULT_ROOT_IN_;

		log_folder_=DEFAULT_LOG_DIRECTORY;
		data_folder_=DEFAULT_DATA_DIRECTORY_NAME_;
		l_image_folder_=DEFAULT_LEFTCAMERA_FOLDER_NAME_ ;
		r_image_folder_= DEFAULT_RIGHTCAMERA_FOLDER_NAME_;
		
		syslogName_=DEFAULT_SYSTEM_LOG_NAME_;
		camlogName_=DEFAULT_CAMERA_LOG_NAME_;
		inoutlogName_=DEFAULT_IN_OUT_LOG_NAME_;	
		starting_time=std::time(0);
}


//utility functions
//////////////////////


std::string OutputSettings::getStringFormat(time_t inTime)
{
    struct std::tm tstruct;
    char buf[100];
    tstruct = *std::localtime(&inTime);
    std::strftime(buf, sizeof(buf), "%Y_%m_%d__%k_%M_%S", &tstruct);
		std::string outString(buf);
		return outString;
		
}


bool OutputSettings::createDir(std::string dir)
{
	//returns true if the directories were succesfully created
	if(!boost::filesystem::exists(dir)) //check if it exists already
	{
		std::string command;
		command="mkdir "+dir;
		if(!system(command.c_str())) //if 0, success , else false
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else{
		return true;//directory already exists
	}
}



//public
///////////////


//init files initializes the file system. true if successfully, false otherwise
//it gets the current time  and attempts to create the file system as follows
//  root_out_dir -->Start Time
//										-	log_folder-->
//																--> sysLogName_
//																--> camLogName_
//																--> inoutlogName_
//										- data_folder-->
//																-->l_image_folder
//																-->r_image_folder

bool OutputSettings::initFiles()
{
	starting_time=std::time(0);
	
	return true;
}


/*
std::string OutputSettings::getDir(DIRECTORIES_ type)
{
	std::string outfile="ERROR";
	switch(type)
	{
		case Root:{
			outfile=root_out_dir_;
			break;
		}
		case StartTime:{
			outfile=root_out_dir_+"/"+getStringFormat(starting_time);
			break;
		}
	}
}*/

}