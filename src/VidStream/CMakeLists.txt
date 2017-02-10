set(VIDSTREAM_SRC "FireWire.cpp;FireWireSettings.cpp")
set(VIDSTREAM_HEADERS "FireWire.hpp;FireWireSettings.hpp")


add_library(VidStream SHARED
	${VIDSTREAM_SRC}
)

	
target_link_libraries(VidStream PUBLIC
		${DC1394_LIBRARIES}
		${OpenCV_LIBRARIES}
		)
