set(SOURCES_ROOT ../src)
set(UTILITY_SRC_ROOT ${SOURCES_ROOT}/utility)
set(BOARD_SRC_ROOT ${SOURCES_ROOT}/game/board)
set(DISPLAY_SRC_ROOT ${SOURCES_ROOT}/game/display)
set(EXCEPTION_SRC_ROOT ${SOURCES_ROOT}/exception)

set(EXCEPTION_SRC
        ${EXCEPTION_SRC_ROOT}/GameException.cpp
        ${EXCEPTION_SRC_ROOT}/NonExistingPieceException.cpp
        ${EXCEPTION_SRC_ROOT}/OutOfBoardException.cpp
        ${EXCEPTION_SRC_ROOT}/PieceOverlapException.cpp ../src/exception/BoardValidationException.cpp ../src/exception/BoardValidationException.hh)

set(BOARD_SRC
        ${BOARD_SRC_ROOT}/SquarePiece.cpp
        ${BOARD_SRC_ROOT}/FixedBoard4x4ForSquarePieces.cpp
        ${BOARD_SRC_ROOT}/FixedBoard4x4ForSquarePieces.hh)

enable_testing()
find_package(GTest MODULE REQUIRED)

add_executable(runPieceTest
        PieceTest.cpp
        ${EXCEPTION_SRC}
        ${BOARD_SRC})
target_link_libraries(runPieceTest PRIVATE GTest::GTest GTest::Main)

target_include_directories(runPieceTest PUBLIC
        ${UTILITY_SRC_ROOT}
        ${BOARD_SRC_ROOT}
        ${DISPLAY_SRC_ROOT}
        ${EXCEPTION_SRC_ROOT}
        ${SOURCES_ROOT})

add_executable(runBoardTest
        BoardTest.cpp
        ${EXCEPTION_SRC}
        ${BOARD_SRC})
target_link_libraries(runBoardTest PRIVATE GTest::GTest GTest::Main)

target_include_directories(runBoardTest PUBLIC
        ${UTILITY_SRC_ROOT}
        ${BOARD_SRC_ROOT}
        ${DISPLAY_SRC_ROOT}
        ${EXCEPTION_SRC_ROOT}
        ${SOURCES_ROOT})