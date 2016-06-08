cmake_minimum_required(VERSION 2.8)

project(SNET)

# include necessary submodules
set(CMAKE_MODULE_PATH "${SNET_SOURCE_DIR}/cmake")

# setting the cpp standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add snet include path
include_directories("${SNET_SOURCE_DIR}/include")

# add tests to build
enable_testing()
add_subdirectory(tests)
