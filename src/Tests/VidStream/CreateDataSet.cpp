
#include "VidStream/PointGrey.hpp"
#include <stdlib.h> 


#define LEFT_PREFIX "l"
#define RIGHT_PREFIX "r"
#define DEFAULT_DIRECTORY "/media/usb0"

int main(int argc, char * argv[])
{
/*	//Get input variables
	if((argc<2)||(argc>3))
	{
		std::cout<<"incorrect number of parameters--expects either of two modes\n";
		std::cout<<"mode 1\n";
		std::cout<<"arg 1 = sub directory\n";
		std::cout<<"Will be stored in "<<DEFAULT_DIRECTORY<<" + arg1 "<<std::endl;
		std::cout<<"mode 2\n";
		std::cout<<"arg 1 = overall directory\n";
		std::cout<<"arg 2 = sub directory\n";
		std::cout<<"Will be stored in arg1 + arg2 "<<std::endl;
		return 1;
	}
	std::string overall_directory,file_prefix,left_dir,right_dir,dataDir;
	if(argc==2)
	{
		overall_directory=DEFAULT_DIRECTORY;
		file_prefix=std::string(argv[1]);

	}
	if(argc==3)
	{
		overall_directory=std::string(argv[1]);
		file_prefix=std::string(argv[2]);
	}
	
	//make the subdirectories
	dataDir=overall_directory;
	dataDir+="/";
	dataDir+=file_prefix;

	left_dir=dataDir;
	left_dir+="/left";

	right_dir=dataDir;
	right_dir+="/right";
	
	
	
	
	
	//check if directories exist and make them 
	if(!boost::filesystem::is_directory(left_dir))
	{
		//make the overall directory
		boost::filesystem::path m(left_dir);
		if(!boost::filesystem::create_directories(m))
		{
			std::cerr<<"Directory failed to be created :" <<left_dir<<std::endl;
			return -1;
		}
	}
	
	//check if directories exist and make them 
	if(!boost::filesystem::is_directory(right_dir))
	{
		//make the overall directory
		boost::filesystem::path m(right_dir);
		if(!boost::filesystem::create_directories(m))
		{
			std::cerr<<"Directory failed to be created :" <<right_dir<<std::endl;
			return -1;
		}
	}

	boost::filesystem::current_path(dataDir);
	
	//initiate input terminal screen
	initscr();
	cbreak();
	nodelay(stdscr,TRUE);
	scrollok(stdscr,TRUE);
	noecho();
	keypad(stdscr,TRUE);
	stereo::PointGrey bumbleBee;
	bumbleBee.n_buffer=18;
	cv::Mat left,right;
	bool run=true;
	
	bumbleBee.dcinit();
	bumbleBee.updateSettings();
	
	if(bumbleBee.openStream())
	{
		u_int64_t stamp,prev;
		prev=0;
		std::stringstream l_fname,r_fname;
		int pressed_key;
		addstr("Recording");
		dataDir+="\\";*/
		/*output variables
		 * 
		 */
	//	std::stringstream msg_;
	//	while(run)
	//	{
	//		addstr("\nPress s to stop Recording\n");
	//		if(bumbleBee.getLatestFrame(left,right,stamp))
	//		{
				/*
				 * Create file name
				 */
	/*			l_fname.str("");
				l_fname<<"left\\" <<"l_"<<stamp<<".ppm";
				
				r_fname.str("");
				r_fname<<"right\\"<<"r_"<<stamp<<".ppm";*/
				/*
				 * save images
				 */
	//			cv::imwrite(l_fname.str(),left);
	//			cv::imwrite(r_fname.str(),right);
	//			float time=(stamp-prev)*1000.0;
	//			msg_.str("");
	//			msg_<<"File : "<<l_fname<<"\t Time Taken : "<<time<<std::endl;
	//			addstr(msg_.str().c_str());
	//			prev=stamp;
	//		}
	//		
	//		else
	//		{
//				addstr("Failed to fetch latest frame");
//			}
			
//			pressed_key=getch();
//			if(pressed_key=='s')
//			{
//					run=false;
//					bumbleBee.closeStream();
//					addstr("Exiting Recording Loop -s to close");
//			}
//			refresh();
//		}
//	}
	
//	int pressed_key;
//	run =true;
//	addstr("s to Close output");
//	while(run)
//	{
//			pressed_key=getch();
//			if(pressed_key=='s')/
//			{
//					run=false;
//					endwin();
//			}
//	}
	
	
	return 1;
}

