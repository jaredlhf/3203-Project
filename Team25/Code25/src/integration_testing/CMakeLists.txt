file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(integration_testing ${srcs}
"src/TestSpPkbIntegration.cpp"
"src/TestPkbQpsIntegration.cpp"
"src/TestFullSpaSystem.cpp" src/SingleSynonymWithoutClauseSystemTest.cpp src/ModifiesSystemTest.cpp src/UsesSystemTest.cpp src/FollowsSystemTest.cpp src/FollowsStarSystemTest.cpp src/ParentSystemTest.cpp src/ParentStarSystemTest.cpp)


target_link_libraries(integration_testing spa)
