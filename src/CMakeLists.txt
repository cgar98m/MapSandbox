add_subdirectory(data)
add_subdirectory(utils)

list(APPEND src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
set(src_files ${src_files} PARENT_SCOPE)
