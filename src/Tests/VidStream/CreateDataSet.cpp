
#include "VidStream/FireWire.hpp"
#include <curses.h>
#include <stdlib.h> 


//#include <stdio.h>
//#include <stdint.h>
//#include <string.h>
//#include <inttypes.h>
//#include <iostream>

#define WIDTH 15

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
	std::cout<<command.str()<<std::endl;
	
	system(char_command.c_str());
	
	command.str("");
	char_command.clear();
	
	command<<"mkdir -p "<<right_dir;
	char_command=command.str();
		std::cout<<command.str()<<std::endl;
	system(char_command.c_str());
	
	std::cout<<"Directories Created\n";
	
	
	
	
	
	initscr();
	cbreak();
	nodelay(stdscr,TRUE);
	scrollok(stdscr,TRUE);
	noecho();
	keypad(stdscr,TRUE);
	
	stereo::FireWire bumbleBee;
	cv::Mat left,right;
	bool run=true;
	
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
		while(run)
		{
			if(bumbleBee.getLatestFrame(left,right,stamp))
			{
				/*
				 * Create file name
				 */
				l_fname.str("");
				l_fname<<left_dir<<"l_"<<stamp<<".ppm";
				
				r_fname.str("");
				r_fname<<right_dir<<"r_"<<stamp<<".ppm";
				
				msg_.str("");
				msg_<<stamp<<std::endl;
				char_msgs_=msg_.str();
				addstr(char_msgs_.c_str());
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
					bumbleBee.streamStop();
					addstr("Exiting Recording Loop");
			}
			refresh();
		}
		endwin();
	}


		//	printw("Current Frame = %d\t, directory = %s\n",frame_number,output_file_name.c_str());
		//	frame_number++;
		//	refresh();
 // }
	
	return 1;
}

