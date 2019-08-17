cmake_minimum_required (VERSION 3.10)

add_library (SbCommon
	src/FormatBuffer.cpp
)

target_include_directories(SbCommon PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)


# Library publishing stuff
#[[
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
]]

# installation
#[[
install(TARGETS SbCommon EXPORT SbCommonTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(TARGETS SbCommon EXPORT SandBoxConfig)
#install(EXPORT SbCoreConfig NAMESPACE SandBox:: DESTINATION lib/cmake/SbCore)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/SbCommonConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/SbCommonConfigVersion.cmake" DESTINATION lib/cmake/SbCommon)
]]