
cmake_minimum_required(VERSION 3.13)

add_library(SbCore)

target_sources(SbCore
#[[	PUBLIC
		App.h
		AppWindow.h
		AppConfiguration.h]]
	PRIVATE
		App.cpp
		AppWindow.cpp
		AppConfiguration.cpp
)

target_include_directories(SbCore PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include/sb-core>
)

message("INSTALL_INTERFACE=${INSTALL_INTERFACE}")

target_link_libraries(SbCore SbCommon SbSpi glfw)