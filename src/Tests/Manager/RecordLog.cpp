#include "Manager/VideoManager.hpp"

#include <iostream>

int main(int argc, char * argv[])
{
	using namespace stereo;
	
	VideoManager myManager_;
	myManager_.beginRecording();

	return 0;
}


/*




stereo::InputManager in("a");
bool isTerminalAlive_;
bool terminate_;
bool running_;
void get();
void mainloop();

boost::shared_mutex mutexisAlive_;
typedef boost::shared_lock<boost::shared_mutex>  ReadLock;
typedef boost::unique_lock<boost::shared_mutex> WriteLock;


int main(int argc, char * argv[])
{
	using namespace stereo;
	
	terminate_=false;
	isTerminalAlive_=false;
	
	
	initscr();
	cbreak();
	nodelay(stdscr,TRUE);
	scrollok(stdscr,TRUE);
	noecho();
	keypad(stdscr,TRUE);
	
	isTerminalAlive_=true;

	
	boost::thread PollingThread(get);
	boost::thread menuThread(mainloop);
	
	PollingThread.join();
	menuThread.join();

	return 0;
}


void mainloop()
{
	unsigned long int abc=0;
	bool keepLooping=true;
	while(keepLooping)
	{
		ReadLock tLock(mutexisAlive_);
		if(!isTerminalAlive_)
		{
			keepLooping=false;
		}
		abc++;
	}
	
	std::cout<<"end"<<abc<<std::endl;
	std::cin.ignore().get(); 
}



void get()
{
	bool loop=true;
	while(loop)
	{
		refresh();
		addstr("polling");
		int pressed_key=getch();
 		if(pressed_key=='s')
		{			
			loop=false;
		}
		usleep(100000);
	}
	endwin();
	WriteLock tLock(mutexisAlive_);
	isTerminalAlive_=false;
	tLock.unlock();
	
	
	std::cout<<"terminal thread Dyiung"<<std::endl;
}*/