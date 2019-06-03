cmake_minimum_required(VERSION 3.12)
project(EternityII)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES_ROOT ./src)

include_directories()

add_executable(${PROJECT_NAME}
        ${SOURCES_ROOT}/main.cpp)