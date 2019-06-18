//
// Created by Guillaume on 18/06/2019.
//


#pragma once
#ifndef ETERNITYII_ISOLVER_HH
#define ETERNITYII_ISOLVER_HH

#include <memory>
#include <IBoard.hh>

namespace etm {
	class ISolver {
	public:
		virtual ~ISolver() = default;

		/**
		 * Propose a solution for the board passed in the input.
		 *
		 * @param board A unique pointer send to the solver. It assumes the ownership of the board for the duration of the solving process.
		 * @return A unique pointer to the solved board, giving back the ownership to the caller.
		 */
		virtual std::unique_ptr<IBoard> solve(std::unique_ptr<IBoard> board) = 0;

		virtual bool canSolvePartiallyFilledBoard() = 0;
	};
}

#endif //ETERNITYII_ISOLVER_HH
