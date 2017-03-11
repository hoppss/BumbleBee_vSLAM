
add_library(Manager 
	PsuedoManager.cpp
	FWmanager.cpp
	)
	
target_link_libraries(Manager  
	Analysis
	VidStream
	FrontEnd
	)

#add_library(DataStructures
#	${RELDATA_SRCS}
#)

#target_link_libraries(DataStructures
#	${BUILD_CV_LIB}
#	)





