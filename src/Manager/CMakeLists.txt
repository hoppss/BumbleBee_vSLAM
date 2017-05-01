
add_library(FireWireVideo
	FireWireManager.cpp
	FireWireSettings.cpp
	)
	
target_link_libraries(FireWireVideo
	boost_thread
	boost_system 
	boost_filesystem
)


add_library(Manager 
	PsuedoManager.cpp
	VideoManager.cpp
	)
	
target_link_libraries(Manager  
	VidStream
	boost_thread
	boost_system 
	boost_filesystem
	ncurses
	FireWireVideo
	)





