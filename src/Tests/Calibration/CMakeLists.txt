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