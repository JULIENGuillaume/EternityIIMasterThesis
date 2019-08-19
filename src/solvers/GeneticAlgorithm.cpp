//
// Created by Guillaume on 20/06/2019.
//

#include <ctime>
#include <DefaultScoreCalculator.hh>
#include <iostream>
#include <TextualDisplay.hh>
#include "GeneticAlgorithm.hh"

etm::GeneticAlgorithm::GeneticAlgorithm(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, double mutationRate, double newRandomIndividualByGen)
		: m_popSize(popSize),
		  m_targetFitness(targetFitness),
		  m_maxGeneration(maxGeneration),
		  m_individualSelected(individualSelected),
		  m_mutationRate(mutationRate),
		  m_newRandomIndividualByGen(newRandomIndividualByGen),
		  m_handleRotation(true) {
	srand(time(nullptr)); //TODO: use better random generator
}

std::array<double, 3> getPopMetrics(std::multimap<double, uint32_t, std::greater<>> const& pop) {
	std::array<double, 3> metrics{};
	double last = 0.0;
	double sum = 0.0;
	double div = 0.0;
	for (auto it = pop.begin(); it!=pop.end(); ++it ) {
		if (it == pop.begin())
			metrics[0] = it->first;
		last = it->first;
		sum += last;
		div += 1.0;
	}
	metrics[1] = last;
	metrics[2] = sum / div;
	return metrics;
}

std::unique_ptr<etm::IBoard> etm::GeneticAlgorithm::solve(std::unique_ptr<IBoard> board) {
	if (this->m_popSize == 0)
		return board;
	this->m_initialState.reserve(board->getCurrentBoardPieces().size());
	for (uint32_t pieceId : board->getCurrentBoardPieces()) {
		this->m_initialState.emplace_back(pieceId, pieceId ? board->getPiecesRotation().at(pieceId) : 0);
	}
	this->m_availablePieces.assign(board->getRemainingPieces().begin(), board->getRemainingPieces().end());
	this->generateInitialPop();
	for (uint32_t genCounter = 0; genCounter < this->m_maxGeneration; ++genCounter) {
		std::cout << "Generation " << genCounter << std::endl;
		this->m_currentPopulation = this->m_futurePopulation;
		//std::cout << "The current population have a size of " << this->m_currentPopulation.size() << std::endl;
		this->evaluateCurrentPop(*board);
		//std::cout << "The evaluation size is " << this->m_scoreToIndividual.size() << std::endl;
		auto metrics = getPopMetrics(this->m_scoreToIndividual);
		std::cout << "Current score:\tBest: " << metrics[0] << "\t\tWorst: " << metrics[1] << "\tAverage: " << metrics[2] << std::endl;
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
		board.removePiece(pos);
	}
	for (uint32_t pos = 0; pos < candidate.size(); ++pos) {
		if (candidate[pos].first == 0) {
			board.removePiece(pos);
		} else {
			board.placePiece(candidate[pos].first, pos, true);
			board.rotatePiece(pos, candidate[pos].second);
		}
	}
}

void etm::GeneticAlgorithm::generateInitialPop() {
	this->m_currentPopulation.reserve(this->m_popSize);
	generateFuturePopWithNRandomIndividual(this->m_popSize);
}

void etm::GeneticAlgorithm::generateFuturePopWithNRandomIndividual(uint32_t n) {
	this->m_futurePopulation.clear();
	this->m_futurePopulation.resize(n, this->m_initialState);
	for (uint32_t i = 0; i < n && i < this->m_popSize; ++i) {
		std::vector<uint32_t> remainingPieces = m_availablePieces;
		for (uint32_t pos = 0; pos < this->m_initialState.size() && !remainingPieces.empty(); ++pos) {
			if (this->m_futurePopulation[i][pos].first == 0) {
				uint32_t valueToPick = rand() % remainingPieces.size(); //TODO: use better random generator
				this->m_futurePopulation[i][pos].first = remainingPieces[valueToPick];
				this->m_futurePopulation[i][pos].second = this->m_handleRotation ? rand() % 4 : 0; //replace with rand
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
		double score = (double)(report.cumulativeScore) / (double)(report.maxScore);
		if (report.cumulativeScore == report.maxScore) {
			//displayPop(this->m_currentPopulation[i]);
			std::unique_ptr<etm::IDisplay> textDisplay = std::make_unique<etm::TextualDisplay>(board);
			textDisplay->refresh();
		}
		this->m_scoreToIndividual.insert({score, i});
		if (score >= this->m_targetFitness)
			return;
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

//TODO: use better random generator
/*
 * Using PMX crossover
 *
 * This crossover guaranty the validity of the generated child
 * However, it may be slow because it involves a lot of copy and swap
 * Moreover, it doesn't take into account the bi-dimensional nature of the board
 */
void etm::GeneticAlgorithm::generateFuturePopWithCrossover() {
	//Generate first the segment of random individual in the next population
	uint32_t randomPopSize = (double)(this->m_popSize) * this->m_newRandomIndividualByGen;
	this->generateFuturePopWithNRandomIndividual(randomPopSize);

	for (auto & m_scoreToSelectedIndividual : this->m_scoreToSelectedIndividuals) {
		this->m_futurePopulation.push_back(this->m_currentPopulation[m_scoreToSelectedIndividual.second]);
	}

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

		//Swap two random segment
		uint32_t segmentPosStart = rand() % child1.size();
		uint32_t segmentPosEnd = segmentPosStart + (rand() % (child1.size() - segmentPosStart));


		std::map<uint32_t, std::pair<uint32_t, uint32_t>> child1ToChild2;
		std::map<uint32_t, std::pair<uint32_t, uint32_t>> child2ToChild1;

		for (uint32_t i = segmentPosStart; i <= segmentPosEnd; ++i) {
			std::swap(child1[i], child2[i]);
			child1ToChild2[child1[i].first] = child2[i];
			child2ToChild1[child2[i].first] = child1[i];
		}


		bool hasChanged = true;
		while (hasChanged) {
			hasChanged = false;
			for (uint32_t i = 0; i < child1.size(); ++i) {
				if (i < segmentPosStart || i > segmentPosEnd) {
					if (child1ToChild2.find(child1[i].first) != child1ToChild2.end()) {
						child1[i] = child1ToChild2.at(child1[i].first);
						hasChanged = true;
					}
					if (child2ToChild1.find(child2[i].first) != child2ToChild1.end()) {
						child2[i] = child2ToChild1.at(child2[i].first);
						hasChanged = true;
					}
				}
			}
		}
		this->m_futurePopulation.push_back(child1);
		if (this->m_futurePopulation.size() < this->m_popSize)
			this->m_futurePopulation.push_back(child2);
	}
}

//TODO: use better random generator
/*
 * Basic mutation system, possibly triggering a swap mutation (exchanging two pieces) or a rotation mutation.
 */
void etm::GeneticAlgorithm::mutateFuturePop() {
	for (std::vector<std::pair<uint32_t, uint32_t>> &population : this->m_futurePopulation) {
		for (uint32_t pos = 0; pos < population.size(); ++pos) {
			double randRate = rand() % 10000;
			randRate /= 10000.0;
			if (randRate <= this->m_mutationRate / 2.0) {
				uint32_t exchangePos = rand() % population.size();
				std::swap(population[pos], population[exchangePos]);
				//std::cout << "Mutation triggered: swapping " << pos << " with " << exchangePos << std::endl;
			}
			if (this->m_handleRotation) {
				randRate = rand() % 10000;
				randRate /= 10000.0;
				if (randRate <= this->m_mutationRate / 2.0) {
					population[pos].second = (population[pos].second + (rand() % 4)) % 4;
					//std::cout << "Mutation triggered: rotation " << std::endl;
				}
			}
		}
	}
}
