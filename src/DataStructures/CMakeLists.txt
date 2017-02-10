
set(TRANSFORMS_SRC "Isometry.cpp")
set(TRANSFORMS_HEADERS "Isometry.hpp")
set(REL_TRANSFORMS_SRC "Transforms/Isometry.cpp")
set(REL_TRANSFORMS_HEADERS "Transforms/Isometry/hpp")

set(RELDATA_SRCS "${REL_TRANSFORMS_SRC}")
set(RELDATA_HEADERS} "${REL_TRANSFORMS_HEADERS}")





add_library(DataStructures
	${RELDATA_SRCS}
	${RELDATA_HEADERS}
)

target_link_libraries(DataStructures
	${BUILD_CV_LIB}
	)
	
target_include_directories(DataStructures PUBLIC
	${RELDATA_HEADERS}
	${BUILD_INCLUDE_DIR}
	)




