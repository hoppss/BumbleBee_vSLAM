
add_library(Manager 
	PsuedoManager.cpp
	VideoManager.cpp
	${easylogging++_SRC}
	)
	
target_link_libraries(Manager  
	Analysis
	VidStream
	FrontEnd
	boost_thread
	boost_system 
	boost_filesystem
	ncurses
	)





