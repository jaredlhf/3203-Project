file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} 
"src/TestConstStore.cpp"
"src/TestEntityStore.cpp"
"src/TestFollowsStar.cpp"
"src/TestFollowsStore.cpp"
"src/TestModifiesStore.cpp"
"src/TestParentStar.cpp"
"src/TestParentStore.cpp"
"src/TestPkbPopulator.cpp"
"src/TestPkbRetriever.cpp"
"src/TestProcStore.cpp"
"src/TestQPS.cpp"
"src/TestQpsClause.cpp"
"src/TestQpsConstants.cpp"
"src/TestQpsFollowsClause.cpp"
"src/TestQpsFollowsStClause.cpp"
"src/TestQpsModifiesClauseResolve.cpp"
"src/TestQpsParentClause.cpp"
"src/TestQpsParentStClause.cpp"
"src/TestQpsPatternClauseResolve.cpp"
"src/TestQpsStringUtils.cpp"
"src/TestQpsSynonyms.cpp"
"src/TestQpsTable.cpp"
"src/TestQpsUsesClauseResolve.cpp"
"src/TestQpsValue.cpp"
"src/TestQpsWildcard.cpp"
"src/TestQueryEvaluator.cpp"
"src/TestQueryParser.cpp"
"src/TestQueryTokenizer.cpp"
"src/TestStmtStore.cpp"
"src/TestUsesStore.cpp"
"src/TestVarStore.cpp"
"src/TestTNode.cpp"
"src/TestSourceProcessor.cpp"
"src/TestTokenizer.cpp"
"src/TestParser.cpp"
"src/TestExpressionParser.cpp"
src/TestDesignExtractor.cpp
src/TestStmtParser.cpp)

target_link_libraries(unit_testing spa)

