
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VidStream)

add_executable(Scan	Scan.cpp)
target_link_libraries(Scan	VidStream)

add_executable(SingleShot	SingleShot.cpp	)
target_link_libraries(SingleShot	VidStream	)

add_executable(Stream Stream.cpp)
target_link_libraries(Stream VidStream)

add_executable(SaveCalibrationImages SaveCalibrationImages.cpp)
target_link_libraries(SaveCalibrationImages VidStream)

add_executable(CreateDataSet CreateDataSet.cpp)
target_link_libraries(CreateDataSet VidStream ncurses boost_system boost_filesystem)

add_executable(FireWireSettings makeFireWireSettings.cpp)
target_link_libraries(FireWireSettings VidStream ${BUILD_CV_LIB})
