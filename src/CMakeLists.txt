set(SOURCES_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILITY_SRC_ROOT ${SOURCES_ROOT}/utility)
set(BOARD_SRC_ROOT ${SOURCES_ROOT}/game/board)
set(DISPLAY_SRC_ROOT ${SOURCES_ROOT}/game/display)

add_executable(${PROJECT_NAME}
        ${SOURCES_ROOT}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${UTILITY_SRC_ROOT}
        ${BOARD_SRC_ROOT}
        ${DISPLAY_SRC_ROOT}
        ${SOURCES_ROOT})