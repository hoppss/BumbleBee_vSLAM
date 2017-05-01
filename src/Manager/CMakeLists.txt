

#	FireWireSettings.cpp
#


add_library(Manager 
	FireWireSettings.cpp
	FireWireManager.cpp
	PsuedoManager.cpp
	VideoManager.cpp
	)
	
target_link_libraries(Manager  
	boost_thread
	boost_system 
	boost_filesystem
	ncurses
	${DC1394_LIBRARIES}
	${OpenCV_LIBRARIES}
	)





