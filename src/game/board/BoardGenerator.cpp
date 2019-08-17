//
// Created by Guillaume Julien on 09/08/2019.
//

#include <iostream>
#include "BoardGenerator.hh"
#include "DynamicSizedBoard.hh"

std::unique_ptr<etm::IBoard> etm::BoardGenerator::generateBoard(uint32_t borderSize, uint32_t numberOfInternalColors, uint32_t borderColor) {
	std::vector<SquarePiece> pieces;
	Size2D size{borderSize, borderSize};

	pieces.resize(borderSize * borderSize, SquarePiece{1, {0, 0, 0, 0}});

	uint32_t maxPos = borderSize * borderSize;
	uint32_t curId = 1;
	for (uint32_t pos = 0; pos < maxPos; ++pos) {
		Position2D curPos{pos % borderSize, pos / borderSize};
		pieces[pos].setId(curId++);
		if (curPos.x == 0) {
			pieces[pos].colorPieceEdge(3, DynamicSizedBoard::boardEdgesColor);
		}
		if (curPos.y == 0) {
			pieces[pos].colorPieceEdge(0, DynamicSizedBoard::boardEdgesColor);
		}
		if (curPos.x == borderSize - 1) {
			pieces[pos].colorPieceEdge(1, DynamicSizedBoard::boardEdgesColor);
		}
		if (curPos.y == borderSize - 1) {
			pieces[pos].colorPieceEdge(2, DynamicSizedBoard::boardEdgesColor);
		}
	}

	static const std::array<std::pair<short, short>, 4> iToMod = {
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
			std::make_pair(-1, 0),
	};
	uint32_t coloredEdges = 0;
	for (uint32_t pos = 0; pos < maxPos; ++pos) {
		Position2D curPos{pos % borderSize, pos / borderSize};
		for (int i = 0; i < 4; ++i) {
			if (pieces[pos].getEdges()[i] == 0) {
				uint32_t color = 2;
				pieces[pos].colorPieceEdge(i, color);
				++coloredEdges;
				Position2D compPos{curPos.x + iToMod[i].first, curPos.y + iToMod[i].second};
				pieces[compPos.x + compPos.y * size.width].colorPieceEdge((i + 2) % 4, color);
				++coloredEdges;
			}
		}
	}

	for (SquarePiece const& piece : pieces) {
		std::cout << "Piece id: " << piece.getId() << "\t||| Colors:\t" << piece.getEdges()[0] << "\t"<< piece.getEdges()[1] << "\t"<< piece.getEdges()[2] << "\t"<< piece.getEdges()[3] << "\t" << std::endl;
	}
	std::cout << "Colored " << coloredEdges << " edges" << std::endl;

	std::unique_ptr<etm::IBoard> board = std::make_unique<etm::DynamicSizedBoard>(pieces, size);

	return board;
}
