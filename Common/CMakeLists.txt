# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

add_library (SbCommon)

target_sources(SbCommon
	PUBLIC
		FormatBuffer.h
		DynamicLibrary.h
		ScopeGuard.h
	PRIVATE
		FormatBuffer.cpp
)

target_include_directories(SbCommon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

