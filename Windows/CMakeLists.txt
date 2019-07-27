# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

set(SbCommon_VERSION 1.0.0)
set(INCLUDE_INSTALL_DIR include/ CACHE STRING "")
set(LIB_INSTALL_DIR lib/ CACHE STRING "")
set(SYSCONFIG_INSTALL_DIR etc/sb/ CACHE STRING "")

add_library (SbWindows
	src/WindowsErrorFormat.cpp
)

target_include_directories(SbWindows PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)