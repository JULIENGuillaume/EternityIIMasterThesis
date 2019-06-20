//
// Created by Guillaume on 20/06/2019.
//


#pragma once
#ifndef ETERNITYII_GENETICALGORITHM_HH
#define ETERNITYII_GENETICALGORITHM_HH

#include <map>
#include "ISolver.hh"

namespace etm {
	class GeneticAlgorithm : public ISolver {
	public:
		GeneticAlgorithm(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, double mutationRate = 0.01);
		~GeneticAlgorithm() override = default;
	public:
		std::unique_ptr<IBoard> solve(std::unique_ptr<IBoard> board) override;
		bool canSolvePartiallyFilledBoard() override;
	protected:
		static void applyCandidateToBoard(IBoard &board, std::vector<uint32_t> const& candidate);
	protected:
		void generateInitialPop(std::vector<uint32_t> const &availablePieceList);
		void evaluateCurrentPop(etm::IBoard &board);
		void selectBestIndividuals();
		void generateFuturePopWithCrossover();
		void mutateFuturePop();
	protected:
		const uint32_t m_popSize;
		const double m_targetFitness;
		const uint32_t m_maxGeneration;
		const uint32_t m_individualSelected;
		const double m_mutationRate;
	protected:
		std::vector<uint32_t> m_initialState;
		std::vector<std::vector<uint32_t>> m_currentPopulation;
		std::vector<std::vector<uint32_t>> m_futurePopulation;
		std::map<double, uint32_t> m_scoreToIndividual;
		std::map<double, uint32_t> m_scoreToSelectedIndividuals;
	};
}

#endif //ETERNITYII_GENETICALGORITHM_HH
