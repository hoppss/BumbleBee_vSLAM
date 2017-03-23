
set(DETECTION_SRC "DetSettings.cpp")
set(DETECTION_HEADERS "DetSettings.hpp")
set(REL_DETECTION_SRC "Detection/DetSettings.cpp;Detection/BRISKdet.cpp")

set(STEREO_FEATURES_SRC "StereoInternal.cpp;StereoRectifiedInternal.cpp;StereoRectifiedFeatures.cpp")
set(STEREO_FEATURES_HEADERS "StereoInternal.hpp;StereoRectifiedInternal.hpp;StereoRectifiedFeatures.cpp")
set(REL_STEREO_FEATURES_SRC "StereoFeatures/StereoInternal.cpp;StereoFeatures/StereoRectifiedInternal.cpp;StereoFeatures/StereoRectifiedFeatures.cpp")

set(WINDOW_SRC "WindowInternal.cpp;SlidingWindow.cpp")
set(WINDOW_HEADERS "WindowInternal.hpp;SlidingWindow.hpp")
set(REL_WINDOW_SRC "Window/WindowInternal.cpp;Window/SlidingWindow.cpp")

add_library(FrontEnd
	${REL_DETECTION_SRC}
	${REL_STEREO_FEATURES_SRC}
	${REL_WINDOW_SRC}
	)

target_link_libraries(FrontEnd
	DataStructures
	)
	




