#include "Manager/VideoManager.hpp"

namespace stereo
{
	
VideoManager::VideoManager()
{
		iso_speed=DC1394_ISO_SPEED_400;
		frame_rate=DC1394_FRAMERATE_15;
		video_mode=DC1394_VIDEO_MODE_1024x768_MONO16;
		color_coding=DC1394_COLOR_CODING_MONO16;
	
		my_logger->info("DEFAULT FIREWIRE SETTINGS IN USE");
		
		recording_=false;
}

VideoManager::~VideoManager()
{
}

////////////////////////////////////////////////////////
////Internal Functions for configuring the bumblebee camera 
///////////////////////////////////////////


///////////////////////////////////
// INternal utility functions
////////////////////////////////


bool VideoManager::checkForError(std::vector< dc1394error_t >& err)
{
	/*cycle through returned error codes, and return false if any are found Unsuccesful
	 * failed to set*/
	bool Error=false;
	for(int index=0;index<err.size();++index)
	{
		if(err.at(index)!=DC1394_SUCCESS)
		{
			Error=true;
		}
	}
	return Error;
}



bool PointGrey::checkUpdated(std::vector< dc1394error_t > err)
{
	/*cycle through returned error codes, and return false if any of the updates
	 * failed to set*/
	bool Success=true;
	for(int index=0;index<err.size();++index)
	{
		if(err.at(index)!=DC1394_SUCCESS)
		{
			Success=false;
		}
	}
	return Success;
}


//////////////////////////


void VideoManager::LatestFrame()
{
	while(recording_)
	{
		
		boost::unique_lock<boost::mutex> lock{mutexLeftQueue_,boost::try_to_lock};
		if(lock.owns_lock())
		{
			my_logger->info("recordThreadLocked");
			leftImgs_.push(2);
			lock.unlock();
		}
		else
		{
			my_logger->info("recordThreadLocked--FAILED");
		}
	}
}

void VideoManager::saveFrame()
{
	while(recording_)
	{
		boost::unique_lock<boost::mutex> lock{mutexLeftQueue_,boost::try_to_lock};
		if(lock.owns_lock())
		{
			my_logger->info("saveThreadLocked");
			leftImgs_.push(10);
			lock.unlock();	
 		}
		else
		{
			my_logger->info("saveThreadLocked--FAILED");
		}
	}
}


///////////////////////////
////PUBLIC FUNCTIONS
////////////////////////


void VideoManager::startRecording()
{
	//begins recording a video sequence
	//spawns two threads
	//thread1-> polling thread for libdc1394,
	//waits until image is available, copies to cv::Mat object if available
	//also monitors the DMA circular buffer and flushes if necessary/WARNS 
	
	//thead2->copies images from a MAT buffer onto the disk
	recording_=true;
	recordThread_=new boost::thread(boost::bind(&VideoManager::LatestFrame,this));
	leftCopyThread_=new boost::thread(boost::bind(&VideoManager::saveFrame,this));
}

void VideoManager::stopRecording()
{
	recording_=false;
}



	
}
