cmake_minimum_required (VERSION 3.10)

include(GoogleTest)

set(SbPalTests_SOURCES
	src/Dummy.cpp
)

if(WIN32)
	set(SbPalTests_SOURCES ${SbPalTest_SOURCES} 
		src/Windows/WindowsErrorFormatTest.cpp
	)
endif()

add_executable(SbPalTests ${SbPalTests_SOURCES})

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
