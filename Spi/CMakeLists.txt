cmake_minimum_required (VERSION 3.13)

add_library (SbSpi src/Spi.cpp)

target_include_directories(SbSpi 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
		$<INSTALL_INTERFACE:include>
)

add_subdirectory(test)