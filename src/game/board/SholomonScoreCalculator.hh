//
// Created by Guillaume Julien on 22/07/2019.
//

#ifndef ETERNITYII_SHOLOMONSCORECALCULATOR_HH
#define ETERNITYII_SHOLOMONSCORECALCULATOR_HH

#include "DefaultScoreCalculator.hh"

namespace etm {
	class SholomonScoreCalculator : public DefaultScoreCalculator {
	public:
		explicit SholomonScoreCalculator(const IBoard &board);
		~SholomonScoreCalculator() override = default;
	public:
		virtual const ScoreReport &computeScore() override;

	};
}

#endif //ETERNITYII_SHOLOMONSCORECALCULATOR_HH
