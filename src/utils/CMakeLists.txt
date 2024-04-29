add_subdirectory(package)

list(APPEND src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/Serializer.cpp)
set(src_files ${src_files} PARENT_SCOPE)
