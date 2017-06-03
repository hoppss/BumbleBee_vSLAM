#change directory TODO
add_executable(Record
	RecordLog.cpp
	)
	
target_link_libraries(Record
	Manager
	)
	
add_executable(PlayBack
	loadFromFile.cpp
	)
	
target_link_libraries(PlayBack
	Manager
	)