#include "Manager/FireWireSettings.hpp"

int main(int argc,char *argv[])
{
	stereo::FireWireSettings a;
	
	cv::FileStorage myFile("/home/ubuntu/ConfigurationFiles/RecordingSettings.xml",cv::FileStorage::WRITE);
	
	myFile<<"RecordingSettings"<<a;
	
	myFile.release();
	
	return 0;
}