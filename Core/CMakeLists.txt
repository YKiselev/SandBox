
cmake_minimum_required(VERSION 3.13)

add_library(SbCore)

target_sources(SbCore
	PRIVATE
		src/App.cpp
		src/AppWindow.cpp
		src/AppConfiguration.cpp
)

target_include_directories(SbCore PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(SbCore SbCommon SbSpi glfw3)

add_subdirectory(test)