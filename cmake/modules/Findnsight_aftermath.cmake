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

set(REQ_VARS ${PCK}_LIBRARY ${PCK}_INCLUDE_DIR)
if(WIN32)
  find_file(
    ${PCK}_RUNTIME
    NAMES GFSDK_Aftermath_Lib.x64.dll
    HINTS
      ${PRAGMA_DEPS_DIR}/nsight_aftermath/bin
  )
  set(REQ_VARS ${REQ_VARS} ${PCK}_RUNTIME)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${PCK}
  REQUIRED_VARS ${REQ_VARS}
)

if(${PCK}_FOUND)
  set(${PCK}_LIBRARIES   ${${PCK}_LIBRARY})
  set(${PCK}_INCLUDE_DIRS ${${PCK}_INCLUDE_DIR})
endif()
