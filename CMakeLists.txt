cmake_minimum_required(VERSION 2.8)

project(SNET)

# add snet include path
include_directories("${SNET_SOURCE_DIR}/include")

# add tests to build
enable_testing()
add_subdirectory(tests)