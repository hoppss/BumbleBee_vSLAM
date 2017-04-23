#include "VidStream/RecordingSettings.hpp"

int main(int argc,char *argv[])
{
	stereo::RecordingSettings a;
	cv::FileStorage fs_l(a.getxmlDir(),cv::FileStorage::WRITE);
	fs_l<<"RecordingSettings"<<a;
	fs_l.release();
	
	cv::FileStorage r_l(a.getxmlDir(),cv::FileStorage::READ);
	stereo::RecordingSettings b;
	
	r_l["RecordingSettings"]>>b;
	r_l.release();
	
	std::cout<<b.outDir_;
	
	return 0;
}