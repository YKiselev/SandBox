cmake_minimum_required (VERSION 3.10)

add_library (SbSpi 
	src/DelegatingWindowEvents.cpp
	src/PersistedConfiguration.cpp
	src/Logger.cpp
)

target_include_directories(SbSpi 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(SbSpi SbCommon glfw)

add_subdirectory(test)

# installation
#[[
install(TARGETS SbSpi EXPORT SbSpiTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(TARGETS SbSpi EXPORT SandBoxConfig)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/SbSpiConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/SbSpiConfigVersion.cmake" DESTINATION lib/cmake/SbSpi)
]]