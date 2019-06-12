//
// Created by Guillaume on 10/06/2019.
//

#include <gtest/gtest.h>
#include "../src/game/board/SquarePiece.hh"

TEST(pieceTests, squarePieceSize) {
		std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(1, std::array<uint32_t, 4>({1, 2, 3, 4}));
		EXPECT_EQ(piece->getPieceDimension(), 4);
}

TEST(pieceTests, squarePieceId) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(2, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getId(), 2);
}

TEST(pieceTests, squarePieceSizeAndEdges) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(3, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getPieceDimension(), piece->getEdges().size());
}

TEST(pieceTests, squarePieceEdges) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(4, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getEdges().size(), 4);
	EXPECT_EQ(piece->getEdges()[0], 1);
	EXPECT_EQ(piece->getEdges()[1], 2);
	EXPECT_EQ(piece->getEdges()[2], 3);
	EXPECT_EQ(piece->getEdges()[3], 4);
}