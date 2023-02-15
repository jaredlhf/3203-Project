file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(unit_testing ${srcs} 
"src/TestConstStore.cpp"
"src/TestEntityStore.cpp"
"src/TestExpressionParser.cpp"
"src/TestFollowsStore.cpp"
"src/TestParser.cpp"
"src/TestPkbPopulator.cpp"
"src/TestPkbRetriever.cpp"
"src/TestProcStore.cpp"
"src/TestQPS.cpp"
"src/TestQpsClause.cpp"
"src/TestQpsConstants.cpp"
"src/TestQpsStringUtils.cpp"
"src/TestQpsSynonyms.cpp"
"src/TestQpsTable.cpp"
"src/TestQpsValue.cpp"
"src/TestQpsWildcard.cpp"
"src/TestQueryEvaluator.cpp"
"src/TestQueryParser.cpp"
"src/TestQueryTokenizer.cpp"
"src/TestSourceProcessor.cpp"
"src/TestStmtStore.cpp"
"src/TestTNode.cpp"
"src/TestTokenizer.cpp"
"src/TestVarStore.cpp")

target_link_libraries(unit_testing spa)

