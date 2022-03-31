
aux_source_directory(. DIR_JSON)
add_library(json ${DIR_JSON})
add_executable(json_test test.cpp)
target_link_libraries(json_test json)
