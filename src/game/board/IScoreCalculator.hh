//
// Created by Guillaume on 17/06/2019.
//


#pragma once
#ifndef ETERNITYII_ISCORECALCULATOR_HH
#define ETERNITYII_ISCORECALCULATOR_HH

#include "ScoreReport.hh"

namespace etm {
	class IScoreCalculator {
	public:
		virtual ~IScoreCalculator() = default;
		virtual ScoreReport const& computeScore() = 0;
		virtual ScoreReport const& getComputedScore() const = 0;
	};
}

#endif //ETERNITYII_ISCORECALCULATOR_HH
