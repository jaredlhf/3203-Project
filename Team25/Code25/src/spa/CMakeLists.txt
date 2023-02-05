file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
<<<<<<< HEAD
add_library(spa ${srcs} ${headers} "src/PKB/PkbPopulator.h" "src/PKB/PkbPopulator.cpp" "src/PKB/PkbRetriever.cpp" "src/PKB/PkbRetriever.h" "src/PKB/placeHolder.h")
=======
add_library(spa ${srcs} ${headers}  "src/VariableStore.cpp" "src/VariableStore.h" "src/ConstantStore.cpp" "src/ConstantStore.h" "src/StatementStore.h" "src/StatementStore.cpp")
>>>>>>> 7035a5e037a8cb0bb47965505eed8736f00c580c
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


