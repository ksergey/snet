cmake_minimum_required(VERSION 2.8)

project(SNET)

# include necessary submodules
set(CMAKE_MODULE_PATH "${SNET_SOURCE_DIR}/cmake")

# configure compiler
include(Compiler)

# add snet include path
include_directories("${SNET_SOURCE_DIR}/include")

# add tests to build
enable_testing()
add_subdirectory(tests)
