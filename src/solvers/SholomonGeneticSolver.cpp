//
// Created by Guillaume Julien on 22/07/2019.
//

#include <algorithm>
#include "SholomonGeneticSolver.hh"

etm::SholomonGeneticSolver::SholomonGeneticSolver(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, double mutationRate, double newRandomIndividualByGen)
		: GeneticAlgorithm(popSize, targetFitness, maxGeneration, individualSelected, mutationRate, newRandomIndividualByGen) {}

void etm::SholomonGeneticSolver::generateFuturePopWithCrossover() {
	//Generate first the segment of random individual in the next population
	uint32_t randomPopSize = (double)(this->m_popSize) * this->m_newRandomIndividualByGen;
	this->generateFuturePopWithNRandomIndividual(randomPopSize);

	while (this->m_futurePopulation.size() < this->m_popSize) {
		//Select the parents
		//TODO: use proportional selection to help the best individuals

		uint32_t posParent1 = rand() % this->m_individualSelected;
		uint32_t posParent2 = rand() % this->m_individualSelected;
		std::vector<std::pair<uint32_t, uint32_t>> child1;
		std::vector<std::pair<uint32_t, uint32_t>> child2;

		auto it = this->m_scoreToSelectedIndividuals.begin();
		for (uint32_t i = 0; i < this->m_scoreToSelectedIndividuals.size() && i <= std::max(posParent1, posParent2); ++i) {
			if (i == posParent1 || i == posParent2) {
				copy(this->m_currentPopulation[it->second].begin(), this->m_currentPopulation[it->second].end(), std::back_inserter(i == posParent1 ? child1 : child2));
				if (posParent1 == posParent2)
					copy(this->m_currentPopulation[it->second].begin(), this->m_currentPopulation[it->second].end(), std::back_inserter(child2));
			}
			++it;
		}

		uint32_t pieceToPlace;
		if ((pieceToPlace = findPieceAgreement()) == 0) {
			if ((pieceToPlace = findBestBuddy()) == 0) {
				pieceToPlace = findBestFitAvailable();
			}
		}
	}
}

uint32_t etm::SholomonGeneticSolver::findPieceAgreement() {
	return 0;
}

uint32_t etm::SholomonGeneticSolver::findBestBuddy() {
	return 0;
}

uint32_t etm::SholomonGeneticSolver::findBestFitAvailable() {
	return 0;
}
