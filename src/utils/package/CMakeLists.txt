add_subdirectory(console)

list(APPEND src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/Sampler.cpp)
set(src_files ${src_files} PARENT_SCOPE)
