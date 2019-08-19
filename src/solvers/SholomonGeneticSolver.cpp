//
// Created by Guillaume Julien on 22/07/2019.
//

#include <algorithm>
#include <queue>
#include <array>
#include "SholomonGeneticSolver.hh"

etm::SholomonGeneticSolver::SholomonGeneticSolver(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, Size2D const& boardSize, double mutationRate, double newRandomIndividualByGen)
		: GeneticAlgorithm(popSize, targetFitness, maxGeneration, individualSelected, mutationRate, newRandomIndividualByGen), m_boardSize(boardSize) {
	m_handleRotation = false;
}

void etm::SholomonGeneticSolver::generateFuturePopWithCrossover() {
	//Generate first the segment of random individual in the next population
	uint32_t randomPopSize = (double) (this->m_popSize) * this->m_newRandomIndividualByGen;
	this->generateFuturePopWithNRandomIndividual(randomPopSize);

	while (this->m_futurePopulation.size() < this->m_popSize) {
		//Select the parents
		//TODO: use proportional selection to help the best individuals

		uint32_t posParent1 = rand() % this->m_individualSelected;
		uint32_t posParent2 = rand() % this->m_individualSelected;
		std::vector<std::pair<uint32_t, uint32_t>> parent1;
		std::vector<std::pair<uint32_t, uint32_t>> parent2;

		auto it = this->m_scoreToSelectedIndividuals.begin();
		for (uint32_t i = 0; i < this->m_scoreToSelectedIndividuals.size() && i <= std::max(posParent1, posParent2); ++i) {
			if (i == posParent1 || i == posParent2) {
				copy(this->m_currentPopulation[it->second].begin(), this->m_currentPopulation[it->second].end(), std::back_inserter(i == posParent1 ? parent1 : parent2));
				if (posParent1 == posParent2)
					copy(this->m_currentPopulation[it->second].begin(), this->m_currentPopulation[it->second].end(), std::back_inserter(parent2));
			}
			++it;
		}

		static const std::array<std::pair<short, short>, 4> iToMod = {
				std::make_pair(0, -1),
				std::make_pair(1, 0),
				std::make_pair(0, 1),
				std::make_pair(-1, 0),
		};

		std::vector<std::pair<uint32_t, uint32_t>> child;
		child.resize(parent1.size(), {0, 0});
		std::queue<uint32_t> availableBoundaries;
		availableBoundaries.emplace(0);
		std::vector<uint32_t> piecesAvailable = this->m_availablePieces;
		while (!availableBoundaries.empty()) {
			bool placementDone = false;
			std::queue<uint32_t> tmpBoundaries = availableBoundaries;
			while (!tmpBoundaries.empty() && !placementDone) {
				uint32_t currentPos = availableBoundaries.front();
				availableBoundaries.pop();
				tmpBoundaries.pop();
				uint32_t piece = findPieceAgreement(child, parent1, parent2, piecesAvailable, currentPos);
				if (piece != 0) {
					placementDone = true;
					child[currentPos].first = piece;
					auto vec = listAvailableBoundariesAtPos(currentPos, child);
					for (uint32_t val : vec) {
						availableBoundaries.emplace(val);
					}
				} else {
					availableBoundaries.emplace(currentPos);
				}
			}
			if (placementDone)
				continue;
			tmpBoundaries = availableBoundaries;
			while (!tmpBoundaries.empty() && !placementDone) {
				uint32_t currentPos = availableBoundaries.front();
				availableBoundaries.pop();
				tmpBoundaries.pop();
				uint32_t piece = findBestBuddy(child, parent1, parent2, piecesAvailable, currentPos);
				if (piece != 0) {
					placementDone = true;
					child[currentPos].first = piece;
					auto vec = listAvailableBoundariesAtPos(currentPos, child);
					for (uint32_t val : vec) {
						availableBoundaries.emplace(val);
					}
				} else {
					availableBoundaries.emplace(currentPos);
				}
			}
			if (placementDone)
				continue;
			tmpBoundaries = availableBoundaries;
			while (!tmpBoundaries.empty() && !placementDone) {
				uint32_t currentPos = availableBoundaries.front();
				availableBoundaries.pop();
				tmpBoundaries.pop();
				uint32_t piece = findBestFitAvailable(child, parent1, parent2, piecesAvailable, currentPos);
				if (piece != 0) {
					placementDone = true;
					child[currentPos].first = piece;
					auto vec = listAvailableBoundariesAtPos(currentPos, child);
					for (uint32_t val : vec) {
						availableBoundaries.emplace(val);
					}
				} else {
					availableBoundaries.emplace(currentPos);
				}
			}
		}
	}
}

std::vector<uint32_t> etm::SholomonGeneticSolver::listAvailableBoundariesAtPos(uint32_t pos, const std::vector<std::pair<uint32_t, uint32_t>> &child) {
	return std::vector<uint32_t>();
}

uint32_t etm::SholomonGeneticSolver::findPieceAgreement(const std::vector<std::pair<uint32_t, uint32_t>> &child,
                                                        const std::vector<std::pair<uint32_t, uint32_t>> &parent1,
                                                        const std::vector<std::pair<uint32_t, uint32_t>> &parent2,
                                                        std::vector<uint32_t> const &piecesAvailable,
                                                        uint32_t pos) {

	return 0;
}

uint32_t etm::SholomonGeneticSolver::findBestBuddy(const std::vector<std::pair<uint32_t, uint32_t>> &child,
                                                   const std::vector<std::pair<uint32_t, uint32_t>> &parent1,
                                                   const std::vector<std::pair<uint32_t, uint32_t>> &parent2,
                                                   std::vector<uint32_t> const &piecesAvailable,
                                                   uint32_t pos) {
	return 0;
}

uint32_t etm::SholomonGeneticSolver::findBestFitAvailable(const std::vector<std::pair<uint32_t, uint32_t>> &child,
                                                          const std::vector<std::pair<uint32_t, uint32_t>> &parent1,
                                                          const std::vector<std::pair<uint32_t, uint32_t>> &parent2,
                                                          std::vector<uint32_t> const &piecesAvailable,
                                                          uint32_t pos) {
	return 0;
}
