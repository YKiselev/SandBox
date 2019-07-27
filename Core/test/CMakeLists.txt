# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)


include(GoogleTest)

add_executable(SbCoreTests 
	src/AppConfigurationTest.cpp
)

target_link_libraries(SbCoreTests 
	SbCore 
	gtest 
	gtest_main
)

gtest_discover_tests(SbCoreTests)

add_custom_command(
     TARGET SbCoreTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbCoreTests
)
