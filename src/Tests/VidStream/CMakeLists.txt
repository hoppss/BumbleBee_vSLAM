
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VidStream)

add_executable(Scan	Scan.cpp)
target_link_libraries(Scan	VidStream)

add_executable(SingleShot	SingleShot.cpp	)
target_link_libraries(SingleShot	VidStream	)

add_executable(Stream Stream.cpp)
target_link_libraries(Stream VidStream)
