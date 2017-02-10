#include "DataStructures/Transforms/Isometry.hpp"

int main(int argc,char** argv )
{
	stereo::Isometry a;
	a.setIdentity();
	a.printH();
	return 0;
}