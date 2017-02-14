#include_directories(${BUILD_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataStructures)

add_executable(CalibrateFromFile
	CalFF.cpp
	)
	
target_link_libraries(CalibrateFromFile
	Calibration
)

#target_include_directories(OverallTest PUBLIC
#		${BUILD_INCLUDE_DIR}
#		)

#target_include_directories(OverallTest PUBLIC
#	${BUILD_INCLUDE_DIR}
#	)
	#	targ
