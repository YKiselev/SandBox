cmake_minimum_required (VERSION 3.13)

add_library (SbMath src/Matrix4D.cpp)

target_include_directories(SbMath PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(test)