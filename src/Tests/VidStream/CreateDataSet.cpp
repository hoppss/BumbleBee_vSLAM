
#include "VidStream/PointGrey.hpp"
#include <curses.h>
#include <stdlib.h> 


#define LEFT_PREFIX "l"
#define RIGHT_PREFIX "r"

int main(int argc, char * argv[])
{
	if(argc!=3)
	{
		std::cout<<"incorrect number of parameters\n";
		std::cout<<"arg 1 =  overall_directory\n";
		std::cout<<"arg 2 = directory Prefix\n";
		return 1;
	}
	

	initscr();
	cbreak();
	nodelay(stdscr,TRUE);
	scrollok(stdscr,TRUE);
	noecho();
	keypad(stdscr,TRUE);
	
	std::string overall_directory,file_prefix,left_dir,right_dir;
	overall_directory=std::string(argv[1]);
	file_prefix=std::string(argv[2]);
	/*Create Directories
	 */
	left_dir=overall_directory;
	left_dir+="/";
	left_dir+=file_prefix;
	left_dir+="/left/";
	
	right_dir=overall_directory;
	right_dir+="/";
	right_dir+=file_prefix;
	right_dir+="/right/";
	
	std::cout<<"Creating Directories\t"<<right_dir<<"\t"<<left_dir<<std::endl;
	std::stringstream command;
	std::string char_command;
	command<<"mkdir -p "<<left_dir;
	char_command=command.str();
	addstr(char_command.c_str());
	
	system(char_command.c_str());
	
	command.str("");
	char_command.clear();
	
	command<<"mkdir -p "<<right_dir;
	char_command=command.str();
	addstr(char_command.c_str());
	system(char_command.c_str());

	stereo::PointGrey bumbleBee;
	bumbleBee.n_buffer=24;
	cv::Mat left,right;
	bool run=true;
	
	bumbleBee.dcinit();
	bumbleBee.updateSettings();
	
	if(bumbleBee.openStream())
	{
		u_int64_t stamp;	
		std::stringstream l_fname,r_fname;
		int pressed_key;
		addstr("Recording");
		/*output variables
		 * 
		 */
		std::stringstream msg_;
		std::string char_msgs_;
		int frame=0;
		while(run)
		{
			if(frame>=15)
			{
				addstr("Press F3 to stop Recording\n");
				frame=0;
			}
			++frame;
			if(bumbleBee.getLatestFrame(left,right,stamp))
			{
				/*
				 * Create file name
				 */
				l_fname.str("");
				l_fname<<left_dir<<"l_"<<stamp<<".ppm";
				
				r_fname.str("");
				r_fname<<right_dir<<"r_"<<stamp<<".ppm";
				/*
				 * save images
				 */
				cv::imwrite(l_fname.str(),left);
				cv::imwrite(r_fname.str(),right);
			}
			
			else
			{
				addstr("Failed to fetch latest frame");
			}
			
			pressed_key=getch();
			if(pressed_key==KEY_F(3))
			{
					run=false;
					bumbleBee.closeStream();
					addstr("Exiting Recording Loop");
			}
			refresh();
		}
		endwin();
	}
	
	return 1;
}

