#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SandBox::SbCommon" for configuration "Debug"
set_property(TARGET SandBox::SbCommon APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SandBox::SbCommon PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/SbCommon-d.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SandBox::SbCommon )
list(APPEND _IMPORT_CHECK_FILES_FOR_SandBox::SbCommon "${_IMPORT_PREFIX}/lib/SbCommon-d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
