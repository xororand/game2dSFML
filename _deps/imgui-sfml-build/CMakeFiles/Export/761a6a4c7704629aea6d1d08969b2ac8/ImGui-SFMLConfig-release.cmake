#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ImGui-SFML::ImGui-SFML" for configuration "Release"
set_property(TARGET ImGui-SFML::ImGui-SFML APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ImGui-SFML::ImGui-SFML PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ImGui-SFML.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ImGui-SFML.dll"
  )

list(APPEND _cmake_import_check_targets ImGui-SFML::ImGui-SFML )
list(APPEND _cmake_import_check_files_for_ImGui-SFML::ImGui-SFML "${_IMPORT_PREFIX}/lib/ImGui-SFML.lib" "${_IMPORT_PREFIX}/bin/ImGui-SFML.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
