include(${CMAKE_SOURCE_DIR}/cmake/pr_common.cmake)

set(PROJ_NAME util_formatted_text)
pr_add_library(${PROJ_NAME} STATIC)

pr_add_dependency(${PROJ_NAME} sharedutils TARGET PUBLIC)
pr_add_dependency(${PROJ_NAME} util_unicode TARGET PUBLIC)

pr_init_module(${PROJ_NAME})

if(UNIX)
    target_link_libraries(${PROJ_NAME} PRIVATE dl)
endif()

pr_finalize(${PROJ_NAME})
