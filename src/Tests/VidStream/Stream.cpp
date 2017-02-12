
#include "VidStream/FireWire.hpp"
#include <chrono>

#define WIDTH 15

std::chrono::high_resolution_clock::time_point begin,end;
int frames_added;
double seconds;

void displayFPS();

int main(int argc,char** argv)
{
	stereo::FireWire bumbleBee;
	cv::Mat left,right;
	
	cv::namedWindow("left",cv::WINDOW_NORMAL);
	cv::namedWindow("right",cv::WINDOW_NORMAL);
	
	bool run=true;
	bumbleBee.openStream();
	frames_added=0;
	seconds=0;
	while(run)
	{
		begin=std::chrono::high_resolution_clock::now();
		int keyNum=cv::waitKey(1);
		if(bumbleBee.getLatestFrame(left,right))
		{
		
			cv::imshow("left",left);
			cv::imshow("right",right);
			displayFPS();
		}
		switch(keyNum)
		{
			case -1:
			{
				break;
			}
			case 1048608: //spacebar pushed
			{
				cv::waitKey(0);
				break;
			}
			case 1048691: //s key pushed
				{
					run=false;
					bumbleBee.streamStop();
					break;
				}
			}
	}

	
	cv::destroyAllWindows();
	return 0;
}

void displayFPS()
{
	frames_added++;
	end=std::chrono::high_resolution_clock::now();
	seconds+=(double) std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
	if(seconds>=1000)
	{
		double latency;
		latency=seconds-1000;
		
		std::cerr<<"FPS ["<<frames_added<<"]\tLatency\t"<<latency<<"(ms)\n";
		
		seconds=0.0;
		frames_added=0;
	}

}

