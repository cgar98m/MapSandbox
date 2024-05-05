add_subdirectory(print)

list(APPEND src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/PackageSampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PackageSerializer.cpp)
set(src_files ${src_files} PARENT_SCOPE)
