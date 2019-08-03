# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)

project (SandBox VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX "-d")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Enable Unicode
add_definitions(-DUNICODE -D_UNICODE)

# Pass target platform defines to source code
if(WIN32)
	add_definitions(-DWIN32=1)
endif()

find_package(glfw3 REQUIRED)
add_library(glfw3 INTERFACE)
target_include_directories(glfw3 INTERFACE ${glfw3_INCLUDE})
target_link_libraries(glfw3 INTERFACE ${glfw3_LIBRARY})


enable_testing()

# Include sub-projects.
add_subdirectory (App)
add_subdirectory (Common)
add_subdirectory (Math)
add_subdirectory (Core)
add_subdirectory (Spi)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.gtest googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
					${CMAKE_CURRENT_BINARY_DIR}/googletest-build
					EXCLUDE_FROM_ALL)

if(WIN32)
	add_subdirectory (Windows)
endif()

# Next line results in error: install(EXPORT "SandBoxConfig" ...) includes target "SbCore" which requires target "glfw3" that is not in the export set.
#install(EXPORT SandBoxConfig NAMESPACE SandBox:: DESTINATION lib)