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
	this->m_initialState.reserve(board->getCurrentBoardPieces().size());
	for (uint32_t pieceId : board->getCurrentBoardPieces()) {
		this->m_initialState.emplace_back(pieceId, pieceId ? board->getPiecesRotation().at(pieceId) : 0);
	}
	this->generateInitialPop({board->getRemainingPieces().begin(), board->getRemainingPieces().end()});
	for (uint32_t genCounter = 0; genCounter < this->m_maxGeneration; ++genCounter) {
		std::cout << "Generation " << genCounter << std::endl;
		this->m_currentPopulation = this->m_futurePopulation;
		//std::cout << "The current population have a size of " << this->m_currentPopulation.size() << std::endl;
		this->evaluateCurrentPop(*board);
		//std::cout << "The evaluation size is " << this->m_scoreToIndividual.size() << std::endl;
		std::cout << "The current best score is " << this->m_scoreToIndividual.begin()->first << std::endl;
		if (this->m_scoreToIndividual.begin()->first >= this->m_targetFitness) {
			applyCandidateToBoard(*board, this->m_currentPopulation[this->m_scoreToIndividual.begin()->second]);
			return board;
		}
		this->selectBestIndividuals();
		this->generateFuturePopWithCrossover();
		this->mutateFuturePop();
	}
	if (!this->m_currentPopulation.empty()) {
		applyCandidateToBoard(*board, this->m_currentPopulation[this->m_scoreToIndividual.begin()->second]);
	}
	return board;
}

bool etm::GeneticAlgorithm::canSolvePartiallyFilledBoard() {
	return true;
}

void etm::GeneticAlgorithm::applyCandidateToBoard(etm::IBoard &board, const std::vector<std::pair<uint32_t, uint32_t>> &candidate) {
	for (uint32_t pos = 0; pos < candidate.size(); ++pos) {
		if (candidate[pos].first == 0)
			board.removePiece(pos);
		else {
			board.placePiece(candidate[pos].first, pos, true);
			board.rotatePiece(pos, candidate[pos].second);
		}
	}
}

void etm::GeneticAlgorithm::generateInitialPop(std::vector<uint32_t> const &availablePieceList) {
	this->m_currentPopulation.reserve(this->m_popSize);
	this->m_futurePopulation.resize(this->m_popSize, this->m_initialState);
	for (uint32_t i = 0; i < this->m_popSize; ++i) {
		std::vector<uint32_t> remainingPieces = availablePieceList;
		for (uint32_t pos = 0; pos < this->m_initialState.size() && !remainingPieces.empty(); ++pos) {
			if (this->m_futurePopulation[i][pos].first == 0) {
				uint32_t valueToPick = rand() % remainingPieces.size(); //TODO: use better random generator
				this->m_futurePopulation[i][pos].first = remainingPieces[valueToPick];
				this->m_futurePopulation[i][pos].second = rand() % 4;
				remainingPieces.erase(remainingPieces.begin() + valueToPick);
			}
		}
	}
}

void etm::GeneticAlgorithm::evaluateCurrentPop(etm::IBoard &board) {
	this->m_scoreToIndividual.clear();
	DefaultScoreCalculator calculator(board);
	for (uint32_t i = 0; i < this->m_currentPopulation.size(); ++i) {
		applyCandidateToBoard(board, this->m_currentPopulation[i]);
		auto report = calculator.computeScore();
		this->m_scoreToIndividual.insert({(double)(report.cumulativeScore) / (double)(report.maxScore), i});
	}
}

void etm::GeneticAlgorithm::selectBestIndividuals() {
	this->m_scoreToSelectedIndividuals.clear();
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
	for (std::vector<std::pair<uint32_t, uint32_t>> &population : this->m_futurePopulation) {
		for (uint32_t pos = 0; pos < population.size(); ++pos) {
			double randRate = rand() % 10000;
			randRate /= 10000;
			if (randRate <= this->m_mutationRate) {
				uint32_t exchangePos = rand() % population.size();
				std::swap(population[pos], population[exchangePos]);
				//std::cout << "Mutation triggered: swapping " << pos << " with " << exchangePos << std::endl;
			}
			randRate = rand() % 10000;
			randRate /= 10000;
			if (randRate <= this->m_mutationRate) {
				population[pos].second = (population[pos].second + (rand() % 4)) % 4;
				//std::cout << "Mutation triggered: rotation " << std::endl;
			}
		}
	}
}
