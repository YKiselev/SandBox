# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)


include(GoogleTest)

add_executable(SandBoxTests 
	Matrix4DTest.cpp 
	Vector3DTest.cpp 
	RadiansTest.cpp 
	FormatBufferTest.cpp
)

target_link_libraries(SandBoxTests gtest gtest_main)
target_link_libraries(SandBoxTests SbMath)
target_link_libraries(SandBoxTests SbCommon)

gtest_discover_tests(SandBoxTests)

add_custom_command(
     TARGET SandBoxTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SandBoxTests
)