cmake_minimum_required(VERSION 3.12)
project(EternityII)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(src)
add_subdirectory(docs)