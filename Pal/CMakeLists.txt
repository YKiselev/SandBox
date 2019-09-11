cmake_minimum_required (VERSION 3.10)

set(SbPal_SOURCES
	src/Pal.cpp
)

if(WIN32)
	set(SbPal_SOURCES ${SbPal_SOURCES} 
		src/Windows/DynamicLibrary.cpp
		src/Windows/WindowsErrorFormat.cpp
		src/Windows/WindowsPal.cpp
	)
endif()

add_library (SbPal	${SbPal_SOURCES})

target_include_directories(SbPal PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(SbPal SbCommon)

add_subdirectory(test)
