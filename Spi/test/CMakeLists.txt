# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)


include(GoogleTest)

add_executable(SbSpiTests 
	src/PersistedConfigurationTest.cpp
	src/LoggerTest.cpp
	src/SharedObjectTest.cpp
)

target_link_libraries(SbSpiTests PRIVATE
	SbSpi 
	GTest::GTest 
	GTest::Main
)

gtest_discover_tests(SbSpiTests)

add_custom_command(
     TARGET SbSpiTests
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND SbSpiTests
)
