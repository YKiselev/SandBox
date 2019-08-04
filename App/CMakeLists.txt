cmake_minimum_required (VERSION 3.13)

if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	set(EXEC_TYPE WIN32)
else()
	set(EXEC_TYPE "")
endif()

add_executable (App "${EXEC_TYPE}" src/SandBox.cpp)

target_link_libraries(App SbSpi SbCore)