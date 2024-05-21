#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sfml-system" for configuration "MinSizeRel"
set_property(TARGET sfml-system APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(sfml-system PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/sfml-system.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/sfml-system-2.dll"
  )

list(APPEND _cmake_import_check_targets sfml-system )
list(APPEND _cmake_import_check_files_for_sfml-system "${_IMPORT_PREFIX}/lib/sfml-system.lib" "${_IMPORT_PREFIX}/bin/sfml-system-2.dll" )

# Import target "sfml-main" for configuration "MinSizeRel"
set_property(TARGET sfml-main APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(sfml-main PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/sfml-main.lib"
  )

list(APPEND _cmake_import_check_targets sfml-main )
list(APPEND _cmake_import_check_files_for_sfml-main "${_IMPORT_PREFIX}/lib/sfml-main.lib" )

# Import target "sfml-window" for configuration "MinSizeRel"
set_property(TARGET sfml-window APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(sfml-window PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/sfml-window.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/sfml-window-2.dll"
  )

list(APPEND _cmake_import_check_targets sfml-window )
list(APPEND _cmake_import_check_files_for_sfml-window "${_IMPORT_PREFIX}/lib/sfml-window.lib" "${_IMPORT_PREFIX}/bin/sfml-window-2.dll" )

# Import target "sfml-graphics" for configuration "MinSizeRel"
set_property(TARGET sfml-graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(sfml-graphics PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/sfml-graphics.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/sfml-graphics-2.dll"
  )

list(APPEND _cmake_import_check_targets sfml-graphics )
list(APPEND _cmake_import_check_files_for_sfml-graphics "${_IMPORT_PREFIX}/lib/sfml-graphics.lib" "${_IMPORT_PREFIX}/bin/sfml-graphics-2.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)