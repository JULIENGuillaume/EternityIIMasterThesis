//
// Created by Guillaume Julien on 09/08/2019.
//

#include <iostream>
#include "BoardGenerator.hh"
#include "DynamicSizedBoard.hh"

std::vector<uint32_t> generateColorList(uint32_t numberOfColors, uint32_t size, uint32_t colorToAvoid, uint32_t offset) {
	std::vector<uint32_t> colorList;
	uint32_t color = 0;

	std::cout << size << std::endl;
	for (uint32_t i = 0; i < size; ++i) {
		color = ((color + 1) % (numberOfColors + offset));
		while (color + offset == colorToAvoid)
			color = ((color + 1) % (numberOfColors + offset));
		colorList.push_back(color + offset);
	}

	std::cout << "ColorList size: " << colorList.size() << std::endl;
	return colorList;
}

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
			pieces[pos].colorPieceEdge(3, borderColor);
		}
		if (curPos.y == 0) {
			pieces[pos].colorPieceEdge(0, borderColor);
		}
		if (curPos.x == borderSize - 1) {
			pieces[pos].colorPieceEdge(1, borderColor);
		}
		if (curPos.y == borderSize - 1) {
			pieces[pos].colorPieceEdge(2, borderColor);
		}
	}

	static const std::array<std::pair<short, short>, 4> iToMod = {
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
			std::make_pair(-1, 0),
	};
	auto colorList = generateColorList(numberOfInternalColors, ((maxPos * 4) - (4 * borderSize)) / 2, borderColor, 1);
	uint32_t coloredEdges = 0;
	for (uint32_t pos = 0; pos < maxPos; ++pos) {
		Position2D curPos{pos % borderSize, pos / borderSize};
		for (int i = 0; i < 4; ++i) {
			if (pieces[pos].getEdges()[i] == 0) {
				std::cout << "ColorList size: " << colorList.size() << std::endl;
				auto it = colorList.begin() + (std::rand() % colorList.size());
				uint32_t color = *it;
				colorList.erase(it);
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
