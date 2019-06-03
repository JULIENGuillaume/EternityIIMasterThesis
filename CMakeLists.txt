cmake_minimum_required(VERSION 3.12)
project(EternityII)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES_ROOT ./src)
set(UTILITY_SRC_ROOT ${SOURCES_ROOT}/utility)
set(BOARD_SRC_ROOT ${SOURCES_ROOT}/game/board)
set(DISPLAY_SRC_ROOT ${SOURCES_ROOT}/game/display)

include_directories(${UTILITY_SRC_ROOT} ${BOARD_SRC_ROOT} ${DISPLAY_SRC_ROOT})

add_executable(${PROJECT_NAME}
        ${SOURCES_ROOT}/main.cpp)