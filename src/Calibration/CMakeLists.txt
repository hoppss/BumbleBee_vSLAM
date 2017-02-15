
add_library(Calibration  
	Calibrator.cpp
	SingleOutput.cpp
	)
	
target_link_libraries(Calibration  
	DataStructures
	)

#add_library(DataStructures
#	${RELDATA_SRCS}
#)

#target_link_libraries(DataStructures
#	${BUILD_CV_LIB}
#	)





