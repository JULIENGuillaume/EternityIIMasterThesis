//
// Created by Guillaume on 17/06/2019.
//


#pragma once
#ifndef ETERNITYII_DEFAULTSCORECALCULATOR_HH
#define ETERNITYII_DEFAULTSCORECALCULATOR_HH

#include <array>
#include "IScoreCalculator.hh"
#include "IBoard.hh"

namespace etm {
	class DefaultScoreCalculator : public IScoreCalculator {
	public:
		explicit DefaultScoreCalculator(IBoard const& board);
		~DefaultScoreCalculator() override = default;
	public:
		const ScoreReport &computeScore() override;
		const ScoreReport &getComputedScore() const override;
	protected:
		std::array<uint32_t, 4> getExpectedColors(Position2D const& pos);
	protected:
		IBoard const& m_board;
		ScoreReport m_report;
	};
}

#endif //ETERNITYII_DEFAULTSCORECALCULATOR_HH
