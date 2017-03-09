
set(TRANSFORMS_SRC "Isometry.cpp")
set(TRANSFORMS_HEADERS "Isometry.hpp")
set(REL_TRANSFORMS_SRC "Transforms/Isometry.cpp")

set(CAMERA_INFO_SRC "Single.cpp;Stereo.cpp")
set(CAMERA_INFO_HEADERS "Single.hpp;Stereo.hpp")
set(REL_CAMERA_INFO_SRC "CameraInfo/Single.cpp;CameraInfo/Stereo.cpp")


set(RELDATA_SRCS "${REL_TRANSFORMS_SRC};${REL_CAMERA_INFO_SRC}")

add_library(DataStructures
	${RELDATA_SRCS}
)

target_link_libraries(DataStructures
	${BUILD_CV_LIB}
	)
