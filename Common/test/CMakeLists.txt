cmake_minimum_required (VERSION 3.13)

include(GoogleTest)

add_executable(SbCommonTests 
	src/FormatBufferTest.cpp
)

target_link_libraries(SbCommonTests 
	SbCommon 
	gtest 
	gtest_main
)

gtest_discover_tests(SbCommonTests)

add_custom_command(
     TARGET SbCommonTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbCommonTests
)
