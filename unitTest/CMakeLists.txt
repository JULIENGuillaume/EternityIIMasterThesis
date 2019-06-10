enable_testing()
find_package(GTest MODULE REQUIRED)
add_executable(runPieceTest PieceTest.cpp ../src/game/board/SquarePiece.cpp)
target_link_libraries(runPieceTest PRIVATE GTest::GTest GTest::Main)
