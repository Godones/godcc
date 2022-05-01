
aux_source_directory(. DIR_JSON)
add_library(dot dot.cpp)
add_library(log log.cpp)


add_executable(tool_test test.cpp)
target_link_libraries(tool_test dot)
target_link_libraries(tool_test log)