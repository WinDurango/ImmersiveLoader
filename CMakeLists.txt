cmake_minimum_required(VERSION 4.0)
project(WinDurango.ImmersiveLoader)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_subdirectory(projects/ImmersiveLoaderCore)

add_custom_target(WinDurango.ImmersiveLoader ALL DEPENDS
    ImmersiveLoaderCore
)