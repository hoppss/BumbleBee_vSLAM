
set(TRANSFORMS_SRC "Isometry.cpp")
set(TRANSFORMS_HEADERS "Isometry.hpp")
set(REL_TRANSFORMS_SRC "Transforms/Isometry.cpp")

set(CAMERA_INFO_SRC "Single.cpp;Stereo.cpp;StereoRect.cpp")
set(CAMERA_INFO_HEADERS "Single.hpp;Stereo.hpp;StereoRect.hpp")
set(REL_CAMERA_INFO_SRC "CameraInfo/Single.cpp;CameraInfo/Stereo.cpp;CameraInfo/StereoRect.cpp")

set(OUTPUT_DATA_SRC "StereoFrame.cpp;StereoFrameStats.cpp;StereoKP.cpp")
set(OUTPUT_DATA_HEADERS "OutputData.hpp;StereoFrame.hpp;StereoFrameStats.hpp;StereoKP.hpp")
set(REL_OUTPUT_DATA_SRC "OutputData/StereoFrame.cpp;OutputData/StereoFrameStats.cpp;OutputData/StereoKP.cpp")


set(RELDATA_SRCS "${REL_TRANSFORMS_SRC};${REL_CAMERA_INFO_SRC};${REL_OUTPUT_DATA_SRC}")

add_library(DataStructures
	${RELDATA_SRCS}
)

target_link_libraries(DataStructures
	${BUILD_CV_LIB}
	)
