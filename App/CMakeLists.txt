cmake_minimum_required (VERSION 3.10)

if(WIN32)
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	#set(EXEC_TYPE WIN32)
	set(EXEC_TYPE "")
else()
	set(EXEC_TYPE "")
endif()

add_executable (App "${EXEC_TYPE}" src/SandBox.cpp)

target_link_libraries(App SbCommon SbCore SbSpi SbPal)

set_target_properties(App PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR>"
    VS_DEBUGGER_COMMAND           "$<TARGET_FILE:App>"
    VS_DEBUGGER_ENVIRONMENT       "PATH=%PATH%;${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)