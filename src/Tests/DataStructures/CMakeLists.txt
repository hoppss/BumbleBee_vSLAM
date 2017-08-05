include_directories(${BUILD_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataStructures)

add_executable(OverallTest
	OverallTest.cpp
	)
	
target_link_libraries(OverallTest
	DataStructures
	FrontEnd
)

target_include_directories(OverallTest PUBLIC
		${BUILD_INCLUDE_DIR}
		)

add_executable(playback 
	streamTest.cpp
	)
	
target_link_libraries(playback
	DataStructures
	FrontEnd
	)
	
