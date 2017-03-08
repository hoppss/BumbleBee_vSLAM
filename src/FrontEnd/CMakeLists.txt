
set(DETECTION_SRC "DetSettings.cpp")
set(DETECTION_HEADERS "DetSettings.hpp")
set(REL_DETECTION_SRC "Detection/DetSettings.cpp;Detection/BRISKdet.cpp")

set(STEREO_FEATURES_SRC "StereoFeatures.cpp;StereoInternal.cpp")
set(STEREO_FEATURES_HEADERS "StereoFeatures.hpp;StereoInternal.hpp")
set(REL_STEREO_FEATURES_SRC "StereoFeatures/StereoFeatures.cpp;StereoFeatures/StereoInternal.cpp")

add_library(FrontEnd
	${REL_DETECTION_SRC}
	${REL_STEREO_FEATURES_SRC}
	)

target_link_libraries(FrontEnd
	DataStructures
	)
	




