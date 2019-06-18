//
// Created by Guillaume on 18/06/2019.
//


#pragma once
#ifndef ETERNITYII_BACKTRACKINGSOLVER_HH
#define ETERNITYII_BACKTRACKINGSOLVER_HH

#include "ISolver.hh"

namespace etm {
	class BacktrackingSolver : public ISolver {
	public:
		BacktrackingSolver() = default;
		~BacktrackingSolver() override = default;
		virtual std::unique_ptr<IBoard> solve(std::unique_ptr<IBoard> board) override;
		virtual bool canSolvePartiallyFilledBoard() override;
	};
}

#endif //ETERNITYII_BACKTRACKINGSOLVER_HH
