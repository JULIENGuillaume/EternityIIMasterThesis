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
#include <DefaultScoreCalculator.hh>
#include <solvers/BacktrackingSolver.hh>
#include <chrono>
#include <solvers/GeneticAlgorithm.hh>
#include <DynamicSizedBoard.hh>
#include <BoardGenerator.hh>

int main(int ac, char **av) {
	try {

		std::vector<etm::SquarePiece> array = {
				etm::SquarePiece(1, {1, 2, 2, 2}),
				etm::SquarePiece(2, {1, 1, 2, 2}),
				etm::SquarePiece(3, {2, 1, 1, 2}),
				etm::SquarePiece(4, {2, 2, 1, 1}),

				etm::SquarePiece(5, {1, 2, 2, 1}),
				etm::SquarePiece(6, {1, 2, 2, 2}),
				etm::SquarePiece(7, {2, 2, 2, 1}),
				etm::SquarePiece(8, {2, 2, 2, 1}),

				etm::SquarePiece(9, {2, 2, 1, 2}),
				etm::SquarePiece(10, {2, 2, 1, 2}),
				etm::SquarePiece(11, {2, 1, 2, 2}),
				etm::SquarePiece(12, {2, 1, 2, 2}),

				etm::SquarePiece(13, {2, 2, 2, 2}),
				etm::SquarePiece(14, {2, 2, 2, 2}),
				etm::SquarePiece(15, {2, 2, 2, 2}),
				etm::SquarePiece(16, {2, 2, 2, 2}),
		};

		std::unique_ptr<etm::IBoard> board = etm::BoardGenerator::generateBoard(16, 1);

		try {
			board->validate();
		} catch (etm::BoardValidationException &e) {
			std::cerr << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		std::unique_ptr<etm::IDisplay> textDisplay = std::make_unique<etm::TextualDisplay>(*board);

		/*textDisplay->refresh();

		board->placePiece(4, 0, false);

		textDisplay->refresh();

		board->rotatePiece(0, 1);

		textDisplay->refresh();

		board->rotatePiece(0, 5);

		textDisplay->refresh();


		board->rotatePiece(0, 1);

		textDisplay->refresh();


		std::cout << "Current score is " << score.cumulativeScore << " out of " << score.maxScore << std::endl;

		std::cout << "Mismatch score is " << board->placePiece(1, 1, false) << std::endl;
		std::cout << "Mismatch score is " << board->placePiece(6, 4, false) << std::endl;
		std::cout << "Mismatch score is " << board->rotatePiece(4, 3) << std::endl;*/

		etm::DefaultScoreCalculator calculator(*board);
		auto const &score = calculator.computeScore();
		//etm::BacktrackingSolver solver;
		etm::GeneticAlgorithm solver(10000, 1.0, 100, 20, 0.05, 0.2);

		/*board->removePiece(0);
		board->removePiece(1);
		board->removePiece(4);*/

		auto ts1 = std::chrono::high_resolution_clock::now();

		try {
			board = solver.solve(std::move(board));
		} catch (std::exception &e) {
			std::cout << "Solver exception: " << e.what() << std::endl;
		}


		auto ts2 = std::chrono::high_resolution_clock::now();
		std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(ts2 - ts1).count() << " ms" << std::endl;

		textDisplay->refresh();
		calculator.computeScore();

		std::cout << "Current score is " << score.cumulativeScore << " out of " << score.maxScore << std::endl;
	} catch (std::exception &e) {
		std::cout << "Software ended with exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}