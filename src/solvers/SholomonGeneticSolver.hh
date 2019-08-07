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
		SholomonGeneticSolver(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, double mutationRate = 0.01, double newRandomIndividualByGen = 0.1);
		~SholomonGeneticSolver() override = default;
	protected:
		virtual void generateFuturePopWithCrossover() override;
	protected:
		uint32_t findPieceAgreement();
		uint32_t findBestBuddy();
		uint32_t findBestFitAvailable();
	};
}

#endif //ETERNITYII_SHOLOMONGENETICSOLVER_HH
