cmake_minimum_required (VERSION 3.10)

include(GoogleTest)

add_executable(SbCommonTests 
	src/FormatBufferTest.cpp
	src/StringConversionTest.cpp
)

target_link_libraries(SbCommonTests 
	SbCommon 
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbCommonTests)

add_custom_command(
     TARGET SbCommonTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbCommonTests
)
