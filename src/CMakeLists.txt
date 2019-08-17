set(SOURCES_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILITY_SRC_ROOT ${SOURCES_ROOT}/utility)
set(BOARD_SRC_ROOT ${SOURCES_ROOT}/game/board)
set(DISPLAY_SRC_ROOT ${SOURCES_ROOT}/game/display)
set(EXCEPTION_SRC_ROOT ${SOURCES_ROOT}/exception)
set(SOLVER_SRC_ROOT ${SOURCES_ROOT}/solvers)

set(EXCEPTION_SRC
        ${EXCEPTION_SRC_ROOT}/GameException.cpp
        ${EXCEPTION_SRC_ROOT}/NonExistingPieceException.cpp
        ${EXCEPTION_SRC_ROOT}/OutOfBoardException.cpp
        ${EXCEPTION_SRC_ROOT}/PieceOverlapException.cpp
        ${EXCEPTION_SRC_ROOT}/BoardValidationException.cpp)

set(BOARD_SRC
        ${BOARD_SRC_ROOT}/SquarePiece.cpp
        ${BOARD_SRC_ROOT}/FixedBoard4x4ForSquarePieces.cpp
        ${BOARD_SRC_ROOT}/DefaultScoreCalculator.cpp game/board/SholomonScoreCalculator.cpp game/board/SholomonScoreCalculator.hh game/board/BoardGenerator.cpp game/board/BoardGenerator.hh game/board/DynamicSizedBoard.cpp game/board/DynamicSizedBoard.hh)

set(DISPLAY_SRC
        ${DISPLAY_SRC_ROOT}/TextualDisplay.cpp)

set(SOLVER_SRC
        ${SOLVER_SRC_ROOT}/BacktrackingSolver.cpp
        ${SOLVER_SRC_ROOT}/GeneticAlgorithm.cpp solvers/SholomonGeneticSolver.cpp solvers/SholomonGeneticSolver.hh)

add_executable(${PROJECT_NAME}
        ${SOURCES_ROOT}/main.cpp
        ${EXCEPTION_SRC}
        ${BOARD_SRC}
        ${DISPLAY_SRC}
        ${SOLVER_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${UTILITY_SRC_ROOT}
        ${BOARD_SRC_ROOT}
        ${DISPLAY_SRC_ROOT}
        ${EXCEPTION_SRC_ROOT}

        ${SOURCES_ROOT}) #TODO: let source root at the end for doxygen