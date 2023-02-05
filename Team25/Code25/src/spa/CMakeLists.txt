file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/PKB/PkbPopulator.h" "src/PKB/PkbPopulator.cpp" "src/PKB/PkbRetriever.cpp" "src/PKB/PkbRetriever.h" "src/PKB/VariableStore.cpp" "src/PKB/VariableStore.h" "src/PKB/ConstantStore.cpp" "src/PKB/ConstantStore.h" "src/PKB/StatementStore.h" "src/PKB/StatementStore.cpp" "src/PKB/ProcedureStore.cpp" "src/PKB/ProcedureStore.h" "src/PKB/FollowsStore.cpp" "src/PKB/FollowsStore.h")
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


