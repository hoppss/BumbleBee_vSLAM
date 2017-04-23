#include "Manager/VideoManager.hpp"

//INITIALIZE_EASYLOGGINGPP

int main(int argc, char * argv[])
{
	using namespace stereo;
	VideoManager bumble_;
	
	bumble_.startRecording();
	
	int a=0;
	while(a<1000000)
	{
		a++;
	}
	bumble_.stopRecording();
	for(int index=0;index<bumble_.leftImgs_.size();index++)
	{
		std::cout<<bumble_.leftImgs_.front()<<",";
		bumble_.leftImgs_.pop();
	}
	return 0;
}