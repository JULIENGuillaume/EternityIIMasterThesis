//
// Created by Guillaume on 20/06/2019.
//

#include <ctime>
#include <DefaultScoreCalculator.hh>
#include <iostream>
#include "GeneticAlgorithm.hh"

etm::GeneticAlgorithm::GeneticAlgorithm(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, double mutationRate) : m_popSize(popSize),
                                                                                                                                                            m_targetFitness(targetFitness),
                                                                                                                                                            m_maxGeneration(maxGeneration),
                                                                                                                                                            m_individualSelected(individualSelected),
                                                                                                                                                            m_mutationRate(mutationRate) {
	srand(time(nullptr)); //TODO: use better random generator
}

std::unique_ptr<etm::IBoard> etm::GeneticAlgorithm::solve(std::unique_ptr<IBoard> board) {
	if (this->m_popSize == 0)
		return board;
	this->m_initialState = board->getCurrentBoardPieces();
	this->generateInitialPop({board->getRemainingPieces().begin(), board->getRemainingPieces().end()});
	for (uint32_t genCounter = 0; genCounter < this->m_maxGeneration; ++genCounter) {
		std::cout << "Generation " << genCounter << std::endl;
		this->m_currentPopulation = this->m_futurePopulation;
		this->evaluateCurrentPop(*board);
		//std::cout << "Best individual have a fitness of " << this->m_scoreToIndividual.begin()->first << std::endl;
		if (this->m_scoreToIndividual.begin()->first >= this->m_targetFitness) {
			applyCandidateToBoard(*board, this->m_currentPopulation[this->m_scoreToIndividual.begin()->second]);
			return board;
		}
		this->selectBestIndividuals();
		this->generateFuturePopWithCrossover();
		this->mutateFuturePop();
	}
	if (!this->m_currentPopulation.empty())
		applyCandidateToBoard(*board, this->m_currentPopulation[this->m_scoreToIndividual.begin()->second]);
	return board;
}

bool etm::GeneticAlgorithm::canSolvePartiallyFilledBoard() {
	return true;
}

void etm::GeneticAlgorithm::applyCandidateToBoard(etm::IBoard &board, std::vector<uint32_t> const& candidate) {
	for (uint32_t pos = 0; pos < candidate.size(); ++pos) {
		if (candidate[pos] == 0)
			board.removePiece(pos);
		else
			board.placePiece(candidate[pos], pos, true);
	}
}

void etm::GeneticAlgorithm::generateInitialPop(std::vector<uint32_t> const &availablePieceList) {
	this->m_currentPopulation.reserve(this->m_popSize);
	this->m_futurePopulation.resize(this->m_popSize, this->m_initialState);
	for (uint32_t i = 0; i < this->m_popSize; ++i) {
		std::vector<uint32_t> remainingPieces = availablePieceList;
		for (uint32_t pos = 0; pos < this->m_initialState.size() && !remainingPieces.empty(); ++pos) {
			if (this->m_futurePopulation[i][pos] == 0) {
				uint32_t valueToPick = rand() % remainingPieces.size(); //TODO: use better random generator
				this->m_futurePopulation[i][pos] = remainingPieces[valueToPick];
				remainingPieces.erase(remainingPieces.begin() + valueToPick);
			}
		}
	}
}

void etm::GeneticAlgorithm::evaluateCurrentPop(etm::IBoard &board) {
	DefaultScoreCalculator calculator(board);
	for (uint32_t i = 0; i < this->m_currentPopulation.size(); ++i) {
		applyCandidateToBoard(board, this->m_currentPopulation[i]);
		auto report = calculator.computeScore();
		this->m_scoreToIndividual.insert({(double)(report.cumulativeScore) / (double)(report.maxScore), i});
	}
}

void etm::GeneticAlgorithm::selectBestIndividuals() {
	auto it = this->m_scoreToIndividual.begin();
	for (uint32_t i = 0; i < this->m_individualSelected; ++i) {
		this->m_scoreToSelectedIndividuals.insert(*it);
		++it;
	}
}

//TODO: put a real crossover
void etm::GeneticAlgorithm::generateFuturePopWithCrossover() {
	auto currentCursor = this->m_scoreToSelectedIndividuals.begin();
	this->m_futurePopulation.clear();
	for (uint32_t i = 0; i < this->m_popSize; ++i) {
		this->m_futurePopulation.emplace_back(this->m_currentPopulation[currentCursor->second]);
		if (++currentCursor == this->m_scoreToSelectedIndividuals.end())
			currentCursor = this->m_scoreToSelectedIndividuals.begin();
	}
}

//TODO: use better random generator
void etm::GeneticAlgorithm::mutateFuturePop() {
	for (std::vector<uint32_t> &population : this->m_futurePopulation) {
		for (uint32_t pos = 0; pos < population.size(); ++pos) {
			if (((double)(rand() % 1000000)) / 1000000.0 <= this->m_mutationRate) {
				uint32_t exchangePos = rand() % population.size();
				uint32_t tmp = population[pos];
				population[pos] = population[exchangePos];
				population[exchangePos] = tmp;
			}
		}
	}
}
