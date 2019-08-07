//
// Created by Guillaume Julien on 22/07/2019.
//

#include "SholomonScoreCalculator.hh"

etm::SholomonScoreCalculator::SholomonScoreCalculator(const etm::IBoard &board) : DefaultScoreCalculator(board) {}

const etm::ScoreReport &etm::SholomonScoreCalculator::computeScore() {
	return DefaultScoreCalculator::computeScore();
}
