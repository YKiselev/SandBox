cmake_minimum_required (VERSION 3.13)

add_library (SbMath)

target_sources(SbMath
	PUBLIC
		Constants.h
		Matrix4D.h
		Radians.h
		Vector3D.h
	PRIVATE
		Matrix4D.cpp
)

target_include_directories(SbMath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})