//
// Created by Guillaume on 03/06/2019.
//

#include <unordered_map>
#include <iostream>
#include <IBoard.hh>
#include <SquarePiece.hh>
#include <FixedBoard4x4ForSquarePieces.hh>
#include <IDisplay.hh>
#include <TextualDisplay.hh>
#include <BoardValidationException.hh>

int main(int ac, char **av) {
	std::array<etm::SquarePiece, 16> array = {
			etm::SquarePiece(1, {1, 2, 3, 4}),
			etm::SquarePiece(2, {1, 1, 3, 4}),
			etm::SquarePiece(3, {1, 1, 3, 4}),
			etm::SquarePiece(4, {1, 1, 3, 4}),

			etm::SquarePiece(5, {1, 1, 3, 4}),
			etm::SquarePiece(6, {1, 2, 3, 4}),
			etm::SquarePiece(7, {1, 2, 3, 4}),
			etm::SquarePiece(8, {1, 2, 3, 4}),

			etm::SquarePiece(9, {1, 2, 3, 4}),
			etm::SquarePiece(10, {1, 2, 3, 4}),
			etm::SquarePiece(11, {1, 2, 3, 4}),
			etm::SquarePiece(12, {1, 2, 3, 4}),

			etm::SquarePiece(13, {2, 2, 3, 4}),
			etm::SquarePiece(14, {2, 2, 3, 4}),
			etm::SquarePiece(15, {2, 2, 3, 4}),
			etm::SquarePiece(16, {2, 2, 3, 4}),
	};

	std::unique_ptr<etm::IBoard> board = std::make_unique<etm::FixedBoard4x4ForSquarePieces>(array);

	try {
		board->validate();
	} catch (etm::BoardValidationException &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}


	std::unique_ptr<etm::IDisplay> textDisplay = std::make_unique<etm::TextualDisplay>(*board);

	textDisplay->refresh();

	board->placePiece(4, 0, false);

	textDisplay->refresh();

	board->rotatePiece(0, 1);

	textDisplay->refresh();

	board->rotatePiece(0, 5);

	textDisplay->refresh();
	return EXIT_SUCCESS;
}