set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FrontEnd)

add_executable(coarseDetect
	simpleDetect.cpp
	)
	
target_link_libraries(coarseDetect
	FrontEnd
)
