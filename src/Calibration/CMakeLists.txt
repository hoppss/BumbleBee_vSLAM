
add_library(Calibration  
	SingleCalibrator.cpp
	SingleOutput.cpp
	SingleConfig.cpp
	StereoConfig.cpp
	StereoCalibrator.cpp
	)
	
target_link_libraries(Calibration  
	DataStructures
	opencv_calib3d
	opencv_imgproc
	)



