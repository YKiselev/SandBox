﻿cmake_minimum_required (VERSION 3.10)

include(GoogleTest)

add_executable(SbMathTests 
	src/Matrix4DTest.cpp 
	src/Vector3DTest.cpp 
	src/RadiansTest.cpp 
)

target_link_libraries(SbMathTests 
	SbMath
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbMathTests)

add_custom_command(
     TARGET SbMathTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbMathTests
)
