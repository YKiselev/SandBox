# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)


include(GoogleTest)

add_executable(SandBoxWindowsTests 
	WindowsErrorFormatTest.cpp
)

target_link_libraries(SandBoxWindowsTests gtest gtest_main)
target_link_libraries(SandBoxWindowsTests SbMath)
target_link_libraries(SandBoxWindowsTests SbCommon)

gtest_discover_tests(SandBoxWindowsTests)
#[[
add_custom_command(
     TARGET SandBoxWindowsTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SandBoxWindowsTests
)
]]