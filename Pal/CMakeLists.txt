cmake_minimum_required (VERSION 3.10)

add_library (SbPal
	src/Pal.cpp
)

target_include_directories(SbPal PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

if(WIN32)
	target_link_libraries(SbPal SbWindows)
endif()

add_subdirectory(test)

