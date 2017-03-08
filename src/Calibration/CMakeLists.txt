
add_library(Calibration  
	SingleCalibrator.cpp
	SingleOutput.cpp
	SingleConfig.cpp
	StereoConfig.cpp
	StereoOutput.cpp
	StereoCalibrator.cpp
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





