
cmake_minimum_required(VERSION 3.13)

add_library(SbCore)

target_sources(SbCore
	PUBLIC
		App.h
		AppWindow.h
		AppConfiguration.h
	PRIVATE
		App.cpp
		AppWindow.cpp
		AppConfiguration.cpp
)

target_include_directories(SbCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

#target_include_directories(SbCore PRIVATE ${glfw_INCLUDE_DIR})

target_link_libraries(SbCore SbCommon SbSpi glfw)