set(_glfw3_HEADER_SEARCH_DIRS
	"/usr/include"
	"/usr/local/include"
	"${CMAKE_SOURCE_DIR}/includes"
	"$ENV{USER_LIB}/glfw-3.3/include" 
)

set(_glfw3_LIB_SEARCH_DIRS
	"/usr/lib"
	"/usr/local/lib"
	"${CMAKE_SOURCE_DIR}/lib"
	"$ENV{USER_LIB}/glfw-3.3/lib-vc2019" 
)

# Search for the header
find_path(glfw3_INCLUDE "GLFW/glfw3.h" PATHS ${_glfw3_HEADER_SEARCH_DIRS} )

# Search for the library
find_library(glfw3_LIBRARY NAMES glfw3 glfw PATHS ${_glfw3_LIB_SEARCH_DIRS} )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(glfw3 DEFAULT_MSG glfw3_LIBRARY glfw3_INCLUDE)