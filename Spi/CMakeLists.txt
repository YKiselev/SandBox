cmake_minimum_required (VERSION 3.13)

add_library (SbSpi)

target_sources(SbSpi
	PUBLIC
		PersistedConfiguration.h
	PRIVATE
		Spi.cpp
)

target_include_directories(SbSpi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})