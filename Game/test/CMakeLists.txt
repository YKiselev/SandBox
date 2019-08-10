# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)


include(GoogleTest)

add_executable(SbGameTests 
	src/GameTest.cpp
)

target_link_libraries(SbGameTests 
	SbSpi 
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbGameTests)

add_custom_command(
     TARGET SbGameTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbGameTests
)
