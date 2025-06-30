include(${CMAKE_SOURCE_DIR}/cmake/pr_common.cmake)

set(PROJ_NAME pr_nsight_aftermath)
set(MODULE_TYPE client)

pr_add_library(${PROJ_NAME} SHARED)

pr_add_dependency(${PROJ_NAME} shared TARGET PUBLIC)
if("${MODULE_TYPE}" STREQUAL "client")
    pr_add_dependency(${PROJ_NAME} client TARGET PUBLIC)
elseif("${MODULE_TYPE}" STREQUAL "server")
    pr_add_dependency(${PROJ_NAME} server TARGET PUBLIC)
endif()
pr_add_dependency(${PROJ_NAME} util_zip TARGET)

pr_add_headers(${PROJ_NAME} "include/")
pr_add_sources(${PROJ_NAME} "src/")

find_package(nsight_aftermath REQUIRED)
pr_add_external_dependency(${PROJ_NAME} nsight_aftermath LIBRARY PRIVATE)

find_package(vulkan REQUIRED)
pr_add_external_dependency(${PROJ_NAME} vulkan HEADER_ONLY PRIVATE)

pr_finalize(${PROJ_NAME})
