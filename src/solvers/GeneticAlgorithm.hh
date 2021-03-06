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
		GeneticAlgorithm(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, double mutationRate = 0.01, double newRandomIndividualByGen = 0.1);
		~GeneticAlgorithm() override = default;
	public:
		std::unique_ptr<IBoard> solve(std::unique_ptr<IBoard> board) override;
		bool canSolvePartiallyFilledBoard() override;
	protected:
		static void applyCandidateToBoard(IBoard &board, const std::vector<std::pair<uint32_t, uint32_t>> &candidate);
	protected:
		void generateInitialPop();
		void generateFuturePopWithNRandomIndividual(uint32_t n);
		virtual void evaluateCurrentPop(etm::IBoard &board);
		void selectBestIndividuals();
		virtual void generateFuturePopWithCrossover(etm::IBoard const &board);
		void mutateFuturePop();
	protected:
		const uint32_t m_popSize;
		const double m_targetFitness;
		const uint32_t m_maxGeneration;
		const uint32_t m_individualSelected;
		const double m_mutationRate;
		const double m_newRandomIndividualByGen;
		bool m_handleRotation;
	protected:
		std::vector<uint32_t> m_availablePieces;
		std::vector<std::pair<uint32_t, uint32_t>> m_initialState;
		std::vector<std::vector<std::pair<uint32_t, uint32_t>>> m_currentPopulation;
		std::vector<std::vector<std::pair<uint32_t, uint32_t>>> m_futurePopulation;
		std::multimap<double, uint32_t, std::greater<>> m_scoreToIndividual;
		std::multimap<double, uint32_t, std::greater<>> m_scoreToSelectedIndividuals;
	};
}

#endif //ETERNITYII_GENETICALGORITHM_HH
