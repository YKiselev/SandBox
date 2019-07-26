# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

set(SbCommon_VERSION 1.0.0)
set(INCLUDE_INSTALL_DIR include/ CACHE STRING "")
set(LIB_INSTALL_DIR lib/ CACHE STRING "")
set(SYSCONFIG_INSTALL_DIR etc/sb/ CACHE STRING "")

add_library (SbCommon)

target_sources(SbCommon
	PRIVATE
		FormatBuffer.cpp
		Sys/Windows/WindowsErrorFormat.cpp
)

target_include_directories(SbCommon PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include/sb-common>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Sys/Windows>  
    $<INSTALL_INTERFACE:include/sb-common/Sys/Windows>
)

# Library publishing stuff

install(TARGETS SbCommon EXPORT SbCommonTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(EXPORT SbCommonTargets
	FILE SbCommonTargets.cmake
	NAMESPACE SandBox::
	DESTINATION lib/cmake/SbCommon
)

include(CMakePackageConfigHelpers)

configure_package_config_file(SbCommonConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/SbCommonConfig.cmake
  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/SbCommon/cmake
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR
)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/SbCommonConfigVersion.cmake"
	VERSION ${SbCommon_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/SbCommonConfig.cmake" 
	"${CMAKE_CURRENT_BINARY_DIR}/SbCommonConfigVersion.cmake"
	DESTINATION lib/cmake/SbCommon
)