file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/QPS/QueryParser.cpp" "src/QPS/QueryParser.h" "src/QPS/ParserResponse.cpp" "src/QPS/ParserResponse.h" "src/QPS/QueryTokenizer.cpp" "src/QPS/QueryTokenizer.h" "src/QPS/QueryEvaluator.cpp" "src/QPS/QueryEvaluator.h" "src/QPS/constants/Synonym.cpp" "src/QPS/constants/Synonym.h" "src/QPS/constants/Constants.cpp" "src/QPS/constants/Constants.h" "src/QPS/Qps.cpp" "src/QPS/Qps.h")

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


