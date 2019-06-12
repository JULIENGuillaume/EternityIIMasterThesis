set(SOURCES_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILITY_SRC_ROOT ${SOURCES_ROOT}/utility)
set(BOARD_SRC_ROOT ${SOURCES_ROOT}/game/board)
set(DISPLAY_SRC_ROOT ${SOURCES_ROOT}/game/display)
set(EXCEPTION_SRC_ROOT ${SOURCES_ROOT}/exception)

set(EXCEPTION_SRC
        ${EXCEPTION_SRC_ROOT}/GameException.cpp
        ${EXCEPTION_SRC_ROOT}/NonExistingPieceException.cpp
        ${EXCEPTION_SRC_ROOT}/OutOfBoardException.cpp
        ${EXCEPTION_SRC_ROOT}/PieceOverlapException.cpp)

set(BOARD_SRC
        ${BOARD_SRC_ROOT}/SquarePiece.cpp
        ${BOARD_SRC_ROOT}/FixedBoard4x4ForSquarePieces.cpp
        ${BOARD_SRC_ROOT}/FixedBoard4x4ForSquarePieces.hh)

add_executable(${PROJECT_NAME}
        ${SOURCES_ROOT}/main.cpp
        ${EXCEPTION_SRC}
        ${BOARD_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${UTILITY_SRC_ROOT}
        ${BOARD_SRC_ROOT}
        ${DISPLAY_SRC_ROOT}
        ${EXCEPTION_SRC_ROOT}

        ${SOURCES_ROOT}) #TODO: let source root at the end for doxygen