//
// Created by Guillaume on 11/06/2019.
//

#include <gtest/gtest.h>
#include "FixedBoard4x4ForSquarePieces.hh"

std::array<etm::SquarePiece, 16> g_array = {
		etm::SquarePiece(1, {1, 2, 3, 4}),
		etm::SquarePiece(2, {1, 2, 3, 4}),
		etm::SquarePiece(3, {1, 2, 3, 4}),
		etm::SquarePiece(4, {1, 2, 3, 4}),

		etm::SquarePiece(5, {1, 2, 3, 4}),
		etm::SquarePiece(6, {1, 2, 3, 4}),
		etm::SquarePiece(7, {1, 2, 3, 4}),
		etm::SquarePiece(8, {1, 2, 3, 4}),

		etm::SquarePiece(9, {1, 2, 3, 4}),
		etm::SquarePiece(10, {1, 2, 3, 4}),
		etm::SquarePiece(11, {1, 2, 3, 4}),
		etm::SquarePiece(12, {1, 2, 3, 4}),

		etm::SquarePiece(13, {1, 2, 3, 4}),
		etm::SquarePiece(14, {1, 2, 3, 4}),
		etm::SquarePiece(15, {1, 2, 3, 4}),
		etm::SquarePiece(16, {1, 2, 3, 4}),
};

TEST(boardTests, boardSizeTest) {
	std::unique_ptr<etm::IBoard> board = std::make_unique<etm::FixedBoard4x4ForSquarePieces>(g_array);
	EXPECT_EQ(board->getSize().height, 4);
	EXPECT_EQ(board->getSize().width, 4);
}

TEST(boardTests, boardDimTest) {
	std::unique_ptr<etm::IBoard> board = std::make_unique<etm::FixedBoard4x4ForSquarePieces>(g_array);
	EXPECT_EQ(board->getPieceDimension(), 4);
}

TEST(boardTests, boardPiecesCheck) {
	std::unique_ptr<etm::IBoard> board = std::make_unique<etm::FixedBoard4x4ForSquarePieces>(g_array);
	EXPECT_EQ(board->getAllPieces().size(), 16);
	EXPECT_EQ(board->getCurrentBoardPieces().size(), 16);
	for (auto const& pieceId : board->getCurrentBoardPieces()) {
		EXPECT_EQ(pieceId, 0);
	}
	EXPECT_EQ(board->getPlayedPieces().size(), 0);
	EXPECT_EQ(board->getPiecesRotation().size(), 0);
	EXPECT_EQ(board->getPlayedPiecesPosition().size(), 0);
}

TEST(boardTests, boardPiecePlacement) {
	std::unique_ptr<etm::IBoard> board = std::make_unique<etm::FixedBoard4x4ForSquarePieces>(g_array);
	board->placePiece(4, 0, false);
	EXPECT_EQ(board->getCurrentBoardPieces()[0], 4);
	EXPECT_EQ(board->getPlayedPieces().size(), 1);
	EXPECT_EQ(board->getPiecesRotation().size(), 1);
	EXPECT_EQ(board->getPlayedPiecesPosition().size(), 1);

	board->placePiece(5, 4, false);
	EXPECT_EQ(board->getCurrentBoardPieces()[0], 4);
	EXPECT_EQ(board->getCurrentBoardPieces()[4], 5);
	EXPECT_EQ(board->getPlayedPieces().size(), 2);
	EXPECT_EQ(board->getPiecesRotation().size(), 2);
	EXPECT_EQ(board->getPlayedPiecesPosition().size(), 2);

	board->removePiece(0);
	EXPECT_EQ(board->getCurrentBoardPieces()[0], 0);
	EXPECT_EQ(board->getCurrentBoardPieces()[4], 5);
	EXPECT_EQ(board->getPlayedPieces().size(), 1);
	EXPECT_EQ(board->getPiecesRotation().size(), 1);
	EXPECT_EQ(board->getPlayedPiecesPosition().size(), 1);
}