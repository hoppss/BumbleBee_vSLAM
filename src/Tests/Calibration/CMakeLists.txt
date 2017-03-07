#include_directories(${BUILD_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataStructures)

add_executable(CalibrateFromFile
	CalFF.cpp
	)
	
target_link_libraries(CalibrateFromFile
	Calibration
)


add_executable(SingleCalibrateFromFile
	SingleCameraFF.cpp
	)
	
target_link_libraries(SingleCalibrateFromFile
	Calibration
)

add_executable(genCalibrationInput
	genCalibrationInput.cpp
	)
	
	target_link_libraries(genCalibrationInput
	Calibration
	)
	
add_executable(StereoFromFile
	StereoFF.cpp
	)
	
	target_link_libraries(StereoFromFile
	Calibration
	)
	
add_executable(genStereoCalibrationInput
	genStereoCalibrationInput.cpp
)

target_link_libraries(genStereoCalibrationInput
	Calibration
	)