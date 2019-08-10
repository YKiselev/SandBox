cmake_minimum_required (VERSION 3.10)

add_library (SbGame SHARED 
	src/Game.cpp 
)

target_link_libraries(SbGame SbSpi SbCommon)

add_subdirectory(test)

include(GenerateExportHeader)

generate_export_header(SbGame)

target_include_directories(SbGame PUBLIC
	${PROJECT_SOURCE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}
)