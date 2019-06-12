//
// Created by Guillaume on 12/06/2019.
//

#include <GameException.hh>
#include <iostream>
#include "TextualDisplay.hh"

etm::TextualDisplay::TextualDisplay(const etm::IBoard &board) : m_board(board) {
	if (m_board.getPieceDimension() != 4) {
		throw GameException("This textual display is only working with 4 dimension pieces");
	}
}

void etm::TextualDisplay::refresh() const {
	auto const &size = m_board.getSize();
	etm::Position2D currentPos;
	auto const &pieceIdOnBoard = m_board.getCurrentBoardPieces();
	std::string display;
	for (currentPos.y = 0; currentPos.y < size.height; ++currentPos.y) {
		for (uint32_t line = 0; line < 4; ++line) {
			for (currentPos.x = 0; currentPos.x < size.width; ++currentPos.x) {
				auto const &edges = m_board.getRotatedEdges(currentPos);
				if (line == 0) {
					display += "***********";
				} else if (line == 1) {
					display += "*    " + std::string(edges[0] < 10 ? "0" : "") + std::to_string(edges[0]) + "    ";
				} else if (line == 2) {
					uint32_t pieceId = pieceIdOnBoard[m_board.getLinearPosition(currentPos)];
					display += "* " + std::string(edges[3] < 10 ? "0" : "") + std::to_string(edges[3]) + " "
					           + std::string(pieceId < 10 ? "0" : "") + std::to_string(pieceId) + " "
					           + std::string(edges[1] < 10 ? "0" : "") + std::to_string(edges[1]) + " ";
				} else if (line == 3) {
					display += "*    " + std::string(edges[2] < 10 ? "0" : "") + std::to_string(edges[2]) + "    ";
				}
			}
			display += "*\n";
		}
	}
	display += "*********************************************";
	std::cout << display << std::endl;
}
