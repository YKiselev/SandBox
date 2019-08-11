cmake_minimum_required (VERSION 3.10)

include(GoogleTest)

add_executable(SbPalTests src/Dummy.cpp)

target_link_libraries(SbPalTests 
	SbPal 
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbPalTests)

add_custom_command(
     TARGET SbPalTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbPalTests
)
