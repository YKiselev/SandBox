cmake_minimum_required (VERSION 3.13)

add_library (SbMath src/Matrix4D.cpp)

target_include_directories(SbMath PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)

# installation

install(TARGETS SbMath EXPORT SbMathTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(TARGETS SbMath EXPORT SandBoxConfig)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/SbMathConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/SbMathConfigVersion.cmake" DESTINATION lib/cmake/SbMath)