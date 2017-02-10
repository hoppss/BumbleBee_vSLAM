
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VidStream)

add_executable(Scan
	Scan.cpp
	)
	
target_link_libraries(Scan
	VidStream
)

#/target_include_directories(OverallTest PUBLIC
#		${BUILD_INCLUDE_DIR}
	#	)

#target_include_directories(OverallTest PUBLIC
#	${BUILD_INCLUDE_DIR}
#	)
	#	targ