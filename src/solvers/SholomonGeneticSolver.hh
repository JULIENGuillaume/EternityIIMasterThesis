//
// Created by Guillaume Julien on 22/07/2019.
//
// This class implement the genetic solver proposed by Sholomon et al. (2013) in A Genetic Algorithm-Based Solver for Very Large Jigsaw Puzzles.
//

#ifndef ETERNITYII_SHOLOMONGENETICSOLVER_HH
#define ETERNITYII_SHOLOMONGENETICSOLVER_HH

#include "GeneticAlgorithm.hh"

namespace etm {
	class SholomonGeneticSolver : public GeneticAlgorithm {
	public:
		SholomonGeneticSolver(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, Size2D const& boardSize, double mutationRate = 0.01, double newRandomIndividualByGen = 0.1);
		~SholomonGeneticSolver() override = default;
	protected:
		void generateFuturePopWithCrossover(etm::IBoard const &board) override;
		std::vector<uint32_t> listAvailableBoundariesAtPos(uint32_t pos, const std::vector<std::pair<uint32_t, uint32_t>> &child);
	protected:
		uint32_t findPieceAgreement(const std::vector<std::pair<uint32_t, uint32_t>> &child,
		                            const std::vector<std::pair<uint32_t, uint32_t>> &parent1,
		                            const std::vector<std::pair<uint32_t, uint32_t>> &parent2,
		                            std::vector<uint32_t> const &piecesAvailable,
		                            uint32_t pos);
		uint32_t findBestBuddy(const std::vector<std::pair<uint32_t, uint32_t>> &child, std::vector<uint32_t> const &piecesAvailable, etm::IBoard const &board, uint32_t pos);
		uint32_t findBestFitAvailable(const std::vector<std::pair<uint32_t, uint32_t>> &child, std::vector<uint32_t> const &piecesAvailable, etm::IBoard const &board, uint32_t pos);
		std::vector<uint32_t> getNeighbours(const std::vector<std::pair<uint32_t, uint32_t>> &board, uint32_t pos);
		uint32_t matchingNeighboursComparison(const std::vector<std::pair<uint32_t, uint32_t>> &board, const std::vector<uint32_t> &neighbours);
	protected:
		Size2D m_boardSize;
	};
}

#endif //ETERNITYII_SHOLOMONGENETICSOLVER_HH
