//
// Created by Guillaume on 10/06/2019.
//

#include <gtest/gtest.h>
#include "../src/game/board/SquarePiece.hh"

TEST(pieceTests, squarePieceSize) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(0, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getPieceDimension(), 4);
}

TEST(pieceTests, squarePieceId) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(0, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getId(), 0);
}

TEST(pieceTests, squarePieceSizeAndEdges) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(0, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getPieceDimension(), piece->getEdges().size());
}

TEST(pieceTests, squarePieceEdges) {
	std::unique_ptr<etm::IPiece> piece = std::make_unique<etm::SquarePiece>(0, std::array<uint32_t, 4>({1, 2, 3, 4}));
	EXPECT_EQ(piece->getPieceDimension(), 4);
}