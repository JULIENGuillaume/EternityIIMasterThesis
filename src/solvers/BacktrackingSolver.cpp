//
// Created by Guillaume on 18/06/2019.
//

#include <iostream>
#include "BacktrackingSolver.hh"

std::unique_ptr<etm::IBoard> etm::BacktrackingSolver::solve(std::unique_ptr<IBoard> board) {
	auto const& availablePieces = board->getRemainingPieces();
	if (availablePieces.size() != board->getAllPieces().size()) {
		std::cerr << "This solver can't solve a board where some pieces are already placed. Returning the board untouched." << std::endl;
		return board;
	}
	std::vector<uint32_t> highestPosInSet;
	highestPosInSet.resize(availablePieces.size(), 0);
	uint32_t posToPlay = 0;
	try {
		while (!availablePieces.empty()) {
			auto it = availablePieces.begin();
			for (uint32_t i = 0; i < highestPosInSet[posToPlay] && it != availablePieces.end(); ++i) {
				++it;
			}
			if (it == availablePieces.end()) {
				if (posToPlay == 0) {
					std::cerr << "We reached the end of possibilities and didn't find any solution." << std::endl;
					return board;
				}
				highestPosInSet[posToPlay] = 0;
				--posToPlay;
				board->removePiece(posToPlay);
				++highestPosInSet[posToPlay];
				continue;
			}
			uint32_t idPieceToPlay = *it;
			uint32_t mismatch = board->placePiece(idPieceToPlay, posToPlay, false);
			for (uint32_t i = 0; i < 4 && mismatch > 0; ++i) {
				mismatch = board->rotatePiece(posToPlay, 1);
			}
			if (mismatch > 0) {
				board->removePiece(posToPlay);
				++highestPosInSet[posToPlay];
			} else {
				++posToPlay;
			}
		}
	} catch (std::exception &e) {
		std::cout << "Solver interrupted by exception: " << e.what() << std::endl;
	}
	return board;
}

bool etm::BacktrackingSolver::canSolvePartiallyFilledBoard() {
	return false;
}
