set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FrontEnd)

add_executable(coarseDetect
	simpleDetect.cpp
	)
	
target_link_libraries(coarseDetect
	FrontEnd
	Analysis
)

add_executable(seq
	sequence.cpp
	)
	
target_link_libraries(seq 
	FrontEnd
	Analysis
	)


##BRIEF descriptor output executables


add_executable(BRISK_BRIEF_BRUTE
	BRISK_BRIEF_BRUTE.cpp
	)
	
target_link_libraries(BRISK_BRIEF_BRUTE
	FrontEnd
)