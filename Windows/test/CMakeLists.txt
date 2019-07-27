cmake_minimum_required (VERSION 3.13)

include(GoogleTest)

add_executable(SbWindowsTests 
	src/WindowsErrorFormatTest.cpp
)

target_link_libraries(SbWindowsTests 
	SbCommon 
	SbWindows
	gtest 
	gtest_main
)

gtest_discover_tests(SbWindowsTests)

add_custom_command(
     TARGET SbWindowsTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbWindowsTests
)
