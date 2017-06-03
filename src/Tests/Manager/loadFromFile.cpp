#include "Manager/PsuedoManager.hpp"
#include "DataStructures/DataSet/BumbleDataSet.hpp"

#include <iostream>

int main(int argc, char * argv[])
{
	using namespace stereo;
	
	//PsuedoManager("/media/usb0/Recordings/1970-01-01__02-01-18");
	BumbleDataSet("/media/usb0/Recordings/1970-01-01__02-01-18");
	return 0;
}
