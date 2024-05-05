add_subdirectory(package)
add_subdirectory(random)

list(APPEND src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/Time.cpp)
set(src_files ${src_files} PARENT_SCOPE)
