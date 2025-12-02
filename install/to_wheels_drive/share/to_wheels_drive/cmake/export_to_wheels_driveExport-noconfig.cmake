#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "to_wheels_drive::to_wheels_drive" for configuration ""
set_property(TARGET to_wheels_drive::to_wheels_drive APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(to_wheels_drive::to_wheels_drive PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libto_wheels_drive.so"
  IMPORTED_SONAME_NOCONFIG "libto_wheels_drive.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS to_wheels_drive::to_wheels_drive )
list(APPEND _IMPORT_CHECK_FILES_FOR_to_wheels_drive::to_wheels_drive "${_IMPORT_PREFIX}/lib/libto_wheels_drive.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
