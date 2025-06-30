set(PCK "nsight_aftermath")

if (${PCK}_FOUND)
  return()
endif()

find_path(${PCK}_INCLUDE_DIR
  NAMES GFSDK_Aftermath.h
  HINTS
    ${PRAGMA_DEPS_DIR}/nsight_aftermath/include
)

find_library(${PCK}_LIBRARY
  NAMES GFSDK_Aftermath_Lib.x64
  HINTS
    ${PRAGMA_DEPS_DIR}/nsight_aftermath/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${PCK}
  REQUIRED_VARS ${PCK}_LIBRARY ${PCK}_INCLUDE_DIR
)

if(${PCK}_FOUND)
  set(${PCK}_LIBRARIES   ${${PCK}_LIBRARY})
  set(${PCK}_INCLUDE_DIRS ${${PCK}_INCLUDE_DIR})
endif()
