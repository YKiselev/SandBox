cmake_minimum_required (VERSION 3.10)

include(GoogleTest)

add_executable(SbWindowsTests 
	src/WindowsErrorFormatTest.cpp
)

target_link_libraries(SbWindowsTests PRIVATE
	SbCommon 
	SbWindows
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbWindowsTests)

add_custom_command(
     TARGET SbWindowsTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbWindowsTests
)
