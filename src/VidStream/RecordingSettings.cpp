#include "VidStream/RecordingSettings.hpp"



namespace stereo {

RecordingSettings::RecordingSettings()
{
		n_buffer=18;
		autoExpose_=true;
		autoShutter_=true;
		autoGain_=true;
		whiteBalance_=false;
		
		brightness_=1;
		shutter_=0.01;
		gain_=600;
		ubal_=63;
		vbal_=20;
		expose_=800;
		
		defaultSet_=true;

		
		recordinglogName_=DEFAULT_LOG_NAME_;
		root_out_dir_=DEFAULT_ROOT_OUT_;
		root_in_dir_=DEFAULT_ROOT_IN_;
		
		xmlName_=DEFAULT_XML_NAME_;
		
		log_folder_=DEFAULT_LOG_DIRECTORY;
		data_folder_=DEFAULT_DATA_DIRECTORY_NAME_;
		l_image_folder_=DEFAULT_LEFTCAMERA_FOLDER_NAME_ ;
		r_image_folder_= DEFAULT_RIGHTCAMERA_FOLDER_NAME_;
		
		starting_time=std::time(0);
		recordinglogName_=std::string(DEFAULT_LOG_NAME_)+"_"+getStringFormat(starting_time);
		
}


//input + output file xml
////////////////////////
void RecordingSettings::read(const cv::FileNode& node)
{

	int temp;
	/*Read from XML */
	node["OutputRootDirectory"]>>root_out_dir_;
	node["LoggingFolder"]>>log_folder_;
	node["DataFolder"]>>data_folder_;
	node["LeftFolder"]>>l_image_folder_;
	node["RightFolder"]>>r_image_folder_;
	node["LoggingFileName"]>>recordinglogName_;
	node["AutoExposure"]>>autoExpose_;
	node["AutoShutter"]>>autoShutter_;
	node["AutoGain"]>>autoGain_;
	node["AutoWhiteBalance"]>>whiteBalance_;
	node["DMA_Buffer"]>>n_buffer;
	node["ShutterSpeed"]>>shutter_;
	node["RAW_gain_val"]>>temp;
	gain_=static_cast<uint32_t>(temp);
	node["RAW_exposure_val"]>>temp;
	expose_=static_cast<uint32_t>(temp);
	node["RAW_vBalance_val"]>>temp;
	vbal_=static_cast<uint32_t>(temp);
	node["RAW_uBalance_val"]>>temp;
	ubal_=static_cast<uint32_t>(temp);
	node["RAW_brightness_val"]>>temp;
	brightness_=static_cast<uint32_t>(temp);
}

void RecordingSettings::write(cv::FileStorage& fs) const
{
		/* write to XML*/
	fs<<"{";
	fs<<"LoggingFolder"<<log_folder_;
	fs<<"DataFolder"<<data_folder_;
	fs<<"LeftFolder"<<l_image_folder_;
	fs<<"RightFolder"<<r_image_folder_;
	fs<<"OutputRootDirectory"<<root_out_dir_;
	fs<<"LoggingFileName"<<recordinglogName_;
	fs<<"AutoExposure"<<autoExpose_;
	fs<<"AutoShutter"<<autoShutter_;
	fs<<"AutoGain"<<autoGain_;
	fs<<"AutoWhiteBalance"<<whiteBalance_;
	fs<<"DMA_Buffer"<<n_buffer;
	fs<<"ShutterSpeed"<<shutter_;
	fs<<"RAW_gain_val"<<(int)gain_;
	fs<<"RAW_exposure_val"<<(int)expose_;
	fs<<"RAW_vBalance_val"<<(int)vbal_;
	fs<<"RAW_uBalance_val"<<(int)ubal_;
	fs<<"RAW_brightness_val"<<(int)brightness_;
	fs<<"}";

}

void RecordingSettings::saveToFile()
{
	std::string outfilename;
	outfilename=root_in_dir_+"/"+xmlName_;
	saveToFile(outfilename);
}


void RecordingSettings::saveToFile(std::string fullDir)
{
	cv::FileStorage fs_l(fullDir,cv::FileStorage::WRITE);
	fs_l<<"RecordingSettings"<<*this;
	fs_l.release();
	std::cout<<"recording Settings saved to "<<fullDir<<std::endl;
}

bool RecordingSettings::readFromFile(std::string inDir)
{
	try { 
		cv::FileStorage fs_l(inDir,cv::FileStorage::READ);
		fs_l["RecordingSettings"]>>*this;
		fs_l.release();
		return true;
	} 
	catch (...) {
		return false;
	}
}




bool RecordingSettings::validateSettings()
{
	bool Success_;
	return Success_;
}

///////////////////////////
//utility  functions
/////////////////////////

bool RecordingSettings::createDir(std::string dir)
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

bool RecordingSettings::createAllDir()
{
	if(root_out_dir_.length()>0)
	{
		//Create out Folder
		if(createDir(root_out_dir_))
		{
			// rootOut-->	
			//				data-->
			//						subdatadir-->
			//								-->leftdir			
			//								-->rightdir
			//				logdir-->
			
			//create the subdirectories
			std::string datadir,subdatadir,logdir,leftdir,rightdir;
			//create absolute path names
			datadir=root_out_dir_+"/"+data_folder_;
			subdatadir=datadir+"/"+getStringFormat(starting_time);
			leftdir=subdatadir+"/"+l_image_folder_;
			rightdir=subdatadir+"/"+r_image_folder_;
			logdir=root_out_dir_+"/"+log_folder_;
			
			//create folders
			bool data,log,left,right,sub;//error flags
			data=createDir(datadir);
			sub=createDir(subdatadir);
			left=createDir(leftdir);
			right=createDir(rightdir);
			log=createDir(logdir);
			if(data&&log&&left&&right)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}



std::string RecordingSettings::getStringFormat(time_t inTime)
{
    struct std::tm tstruct;
    char buf[100];
    tstruct = *std::localtime(&inTime);
    std::strftime(buf, sizeof(buf), "%Y_%m_%d__%k_%M_%S", &tstruct);
		std::string outString(buf);
		
		return outString;
		
}





}