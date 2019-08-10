# CMakeList.txt : CMake project for SandBox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

add_library (SbWindows
	src/WindowsErrorFormat.cpp
	src/WindowsDynamicLibrary.cpp
)

target_include_directories(SbWindows PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)

# installation
#[[
install(TARGETS SbWindows EXPORT SbWindowsTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(TARGETS SbWindows EXPORT SandBoxConfig)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/SbWindowsConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/SbWindowsConfigVersion.cmake" DESTINATION lib/cmake/SbWindows)
]]