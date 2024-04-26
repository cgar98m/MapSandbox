cmake_minimum_required(VERSION 3.15)

project(MapSandbox VERSION 1.1.0)

add_subdirectory(src)

add_executable(MapSandbox ${src_files})
target_include_directories(MapSandbox PRIVATE include)

add_custom_command(TARGET MapSandbox
    PRE_BUILD
    COMMAND cmd //C "C:\\Program Files\\Microsoft\ Visual\ Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcbars64.bat")
