cmake_minimum_required (VERSION 3.10)

include(GoogleTest)

add_executable(SbCoreTests 
	src/AppConfigurationTest.cpp
)

target_link_libraries(SbCoreTests 
	SbCore 
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbCoreTests)

add_custom_command(
     TARGET SbCoreTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbCoreTests
)
