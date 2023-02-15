file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} "src/TestVarStore.cpp" "src/TestProcStore.cpp" "src/TestConstStore.cpp" "src/TestStmtStore.cpp" "src/TestFollowsStore.cpp" "src/TestQueryTokenizer.cpp" "src/TestQpsSynonyms.cpp" "src/TestQueryEvaluator.cpp" "src/TestQPS.cpp" "src/TestTNode.cpp" "src/TestSourceProcessor.cpp" "src/TestTokenizer.cpp" "src/TestParser.cpp" "src/TestExpressionParser.cpp" "src/TestQpsClause.cpp" "src/TestQpsValue.cpp" "src/TestQpsWildcard.cpp" "src/TestQpsStringUtils.cpp" "src/TestQpsTable.cpp")
target_link_libraries(unit_testing spa)

