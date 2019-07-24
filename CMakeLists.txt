# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)

project ("SandBox")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PREFIX_PATH $ENV{USER_LIB})

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#option(Download_GTEST "Download GoogleTest?" OFF)


find_package(glfw REQUIRED)
if(glfw_LIBRARY AND glfw_INCLUDE_DIR)
	add_library(glfw INTERFACE)
	target_include_directories(glfw INTERFACE ${glfw_INCLUDE_DIR})
	target_link_libraries(glfw INTERFACE ${glfw_LIBRARY})
else()
	message(FATAL_ERROR "GLFW library not found!")
endif()


#message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} ")
#message("glfw_INCLUDE_DIR=${glfw_INCLUDE_DIR}, glfw_LIBRARY=${glfw_LIBRARY}")


# Include sub-projects.
add_subdirectory (App)
add_subdirectory (Common)
add_subdirectory (Math)
add_subdirectory (Core)
add_subdirectory (Spi)

#if(Download_GTEST)
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
#endif(Download_GTEST)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
					${CMAKE_CURRENT_BINARY_DIR}/googletest-build
					EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
	include_directories("${gtest_SOURCE_DIR}/include")
endif()


enable_testing()
add_subdirectory (Test)
