
cmake_minimum_required(VERSION 3.13)

add_library(SbCore)
add_library(SandBox::SbCore ALIAS SbCore)

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

if(SANDBOX)
	add_subdirectory(test)
endif()

# installation

install(TARGETS SbCore EXPORT SbCoreTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

install(TARGETS SbCore EXPORT SandBoxConfig)
#install(EXPORT SbCoreConfig NAMESPACE SandBox:: DESTINATION lib/cmake/SbCore)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/SbCoreConfigVersion.cmake"
    VERSION
        ${PROJECT_VERSION}
    COMPATIBILITY
        AnyNewerVersion
)
install(FILES "${PROJECT_BINARY_DIR}/SbCoreConfigVersion.cmake" DESTINATION lib/cmake/SbCore)