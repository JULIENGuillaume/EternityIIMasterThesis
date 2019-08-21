//
// Created by Guillaume Julien on 22/07/2019.
//

#include <algorithm>
#include <queue>
#include <array>
#include <iostream>
#include "SholomonGeneticSolver.hh"

etm::SholomonGeneticSolver::SholomonGeneticSolver(uint32_t popSize, double targetFitness, uint32_t maxGeneration, uint32_t individualSelected, Size2D const& boardSize, double mutationRate, double newRandomIndividualByGen)
		: GeneticAlgorithm(popSize, targetFitness, maxGeneration, individualSelected, mutationRate, newRandomIndividualByGen), m_boardSize(boardSize) {
	m_handleRotation = false;
}

static void removePieceFromVec(std::vector<uint32_t> &vec, uint32_t piece) {
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		if (*it == piece) {
			vec.erase(it);
			return;
		}
	}
}

void etm::SholomonGeneticSolver::generateFuturePopWithCrossover(etm::IBoard const &board) {
	//std::cout << "Entering sholomon" << std::endl;
	//Generate first the segment of random individual in the next population
	uint32_t randomPopSize = (double) (this->m_popSize) * this->m_newRandomIndividualByGen;
	this->generateFuturePopWithNRandomIndividual(randomPopSize);

	for (auto & m_scoreToSelectedIndividual : this->m_scoreToSelectedIndividuals) {
		this->m_futurePopulation.push_back(this->m_currentPopulation[m_scoreToSelectedIndividual.second]);
	}

	while (this->m_futurePopulation.size() < this->m_popSize) {
		//std::cout << "Pop: " << this->m_futurePopulation.size() << "/" << this->m_popSize << std::endl;
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

		//std::cout << "Parent selected" << std::endl;

		std::vector<std::pair<uint32_t, uint32_t>> child;
		child.resize(parent1.size(), {0, 0});
		std::queue<uint32_t> availableBoundaries;
		availableBoundaries.emplace(0);
		std::vector<uint32_t> piecesAvailable = this->m_availablePieces;
		while (!availableBoundaries.empty()) {
			//std::cout << "Pieces available and boundaries: " << piecesAvailable.size() << " " << availableBoundaries.size() << std::endl;
		//	if (piecesAvailable.empty())
		//		exit(0);
			bool placementDone = false;
			std::queue<uint32_t> tmpBoundaries = availableBoundaries;
			//std::cout << "Start of step 1..." << std::endl;
			while (!tmpBoundaries.empty() && !placementDone) {
				uint32_t currentPos = availableBoundaries.front();
				availableBoundaries.pop();
				tmpBoundaries.pop();
				if (child[currentPos].first == 0) {
					uint32_t piece = findPieceAgreement(child, parent1, parent2, piecesAvailable, currentPos);
					//std::cout << "Piece is " << piece << std::endl;
					if (piece != 0) {
						//std::cout << "A piece has been found !" << std::endl;
						placementDone = true;
						child[currentPos].first = piece;
						removePieceFromVec(piecesAvailable, piece);
						auto vec = listAvailableBoundariesAtPos(currentPos, child);
						for (uint32_t val : vec) {
							availableBoundaries.emplace(val);
						}
					} else {
						availableBoundaries.emplace(currentPos);
					}
				}
			}
			//std::cout << "End of step 1" << std::endl;
			if (placementDone)
				continue;
			tmpBoundaries = availableBoundaries;
			//std::cout << "Start of step 2..." << std::endl;
			while (!tmpBoundaries.empty() && !placementDone) {
				uint32_t currentPos = availableBoundaries.front();
				availableBoundaries.pop();
				tmpBoundaries.pop();
				if (child[currentPos].first == 0) {
					uint32_t piece = findBestBuddy(child, piecesAvailable, board, currentPos);
					if (piece != 0) {
						//std::cout << "A piece has been found !" << std::endl;
						placementDone = true;
						child[currentPos].first = piece;
						removePieceFromVec(piecesAvailable, piece);
						auto vec = listAvailableBoundariesAtPos(currentPos, child);
						for (uint32_t val : vec) {
							availableBoundaries.emplace(val);
						}
					} else {
						availableBoundaries.emplace(currentPos);
					}
				}
			}
			//std::cout << "End of step 2" << std::endl;
			if (placementDone)
				continue;
			tmpBoundaries = availableBoundaries;
			//std::cout << "Start of step 3..." << std::endl;
			while (!tmpBoundaries.empty() && !placementDone) {
				uint32_t currentPos = availableBoundaries.front();
				availableBoundaries.pop();
				tmpBoundaries.pop();
				if (child[currentPos].first == 0) {
					uint32_t piece = findBestFitAvailable(child, piecesAvailable, board, currentPos);
					if (piece != 0) {
						//std::cout << "A piece has been found !" << std::endl;
						placementDone = true;
						child[currentPos].first = piece;
						removePieceFromVec(piecesAvailable, piece);
						auto vec = listAvailableBoundariesAtPos(currentPos, child);
						for (uint32_t val : vec) {
							availableBoundaries.emplace(val);
						}
					} else {
						availableBoundaries.emplace(currentPos);
					}
				}
			}
			//std::cout << "End of step 3" << std::endl;
		}
		this->m_futurePopulation.push_back(child);
	}
}

std::vector<uint32_t> etm::SholomonGeneticSolver::listAvailableBoundariesAtPos(uint32_t pos, const std::vector<std::pair<uint32_t, uint32_t>> &child) {
	Position2D pos2D{pos % this->m_boardSize.width, pos / this->m_boardSize.height};
	static const std::array<std::pair<short, short>, 4> iToMod = {
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
			std::make_pair(-1, 0),
	};

	std::vector<uint32_t> availableBoundaries;
	for (auto const& mod : iToMod) {
		Position2D neighbourPos{pos2D.x + mod.first, pos2D.y + mod.second};
		if (neighbourPos.x < 0 || neighbourPos.x >= m_boardSize.width || neighbourPos.y < 0 || neighbourPos.y >= m_boardSize.height)
			continue;
		uint32_t linePos = neighbourPos.x + neighbourPos.y * m_boardSize.width;
		if (child[linePos].first == 0)
			availableBoundaries.emplace_back(linePos);
	}
	//std::cout << "Returning " << availableBoundaries.size() << " new boundaries" << std::endl;
	return availableBoundaries;
}

uint32_t etm::SholomonGeneticSolver::findPieceAgreement(const std::vector<std::pair<uint32_t, uint32_t>> &child,
                                                        const std::vector<std::pair<uint32_t, uint32_t>> &parent1,
                                                        const std::vector<std::pair<uint32_t, uint32_t>> &parent2,
                                                        std::vector<uint32_t> const &piecesAvailable,
                                                        uint32_t pos) {
//	std::cout << "Entering find piece agreement" << std::endl;
	auto neighbours = getNeighbours(child, pos);
//	std::cout << "Got neighbours" << std::endl;
	uint32_t pieceAtParent1 = matchingNeighboursComparison(parent1, neighbours);
	if (pieceAtParent1 == 0)
		return 0;
	for (uint32_t piece : piecesAvailable)
		if (piece == pieceAtParent1)
			return 0;
	uint32_t pieceAtParent2 = matchingNeighboursComparison(parent2, neighbours);
	if (pieceAtParent2 == pieceAtParent1)
		return pieceAtParent1;
	return 0;
}

uint32_t etm::SholomonGeneticSolver::findBestBuddy(const std::vector<std::pair<uint32_t, uint32_t>> &child, std::vector<uint32_t> const &piecesAvailable, etm::IBoard const &board, uint32_t pos) {
	std::vector<uint32_t> matchingPieces = piecesAvailable;
	Position2D pos2D{pos % this->m_boardSize.width, pos / this->m_boardSize.height};
	static const std::array<std::pair<short, short>, 4> iToMod = {
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
			std::make_pair(-1, 0),
	};

	for (uint32_t i = 0; i < 4 && !matchingPieces.empty(); ++i) {
		Position2D neighbourPos{pos2D.x + iToMod[i].first, pos2D.y + iToMod[i].second};
		uint32_t colorToMatch = 0;
		if (neighbourPos.x < 0 || neighbourPos.x >= m_boardSize.width || neighbourPos.y < 0 || neighbourPos.y >= m_boardSize.height) {
			colorToMatch = board.getDefaultEdgeColor();
		} else {
			uint32_t linePos = neighbourPos.x + neighbourPos.y * m_boardSize.width;
			uint32_t childPiece = child[linePos].first;
			if (childPiece != 0) {
				colorToMatch = board.getPiece(childPiece).getEdges()[(i + 2) % 4];
			}
		}
		if (colorToMatch == 0)
			continue;
		std::vector<uint32_t> validPieces;
		for (uint32_t piece : matchingPieces) {
			if (board.getPiece(piece).getEdges()[i] == colorToMatch)
				validPieces.push_back(piece);
		}
		matchingPieces = validPieces;
	}
	if (matchingPieces.empty())
		return 0;
	return matchingPieces[rand() % matchingPieces.size()];
}

uint32_t etm::SholomonGeneticSolver::findBestFitAvailable(const std::vector<std::pair<uint32_t, uint32_t>> &child, std::vector<uint32_t> const &piecesAvailable, etm::IBoard const &board, uint32_t pos) {
	Position2D pos2D{pos % this->m_boardSize.width, pos / this->m_boardSize.height};
	static const std::array<std::pair<short, short>, 4> iToMod = {
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
			std::make_pair(-1, 0),
	};

	std::array<uint32_t, 4> colors{};
	for (uint32_t i = 0; i < 4; ++i) {
		Position2D neighbourPos{pos2D.x + iToMod[i].first, pos2D.y + iToMod[i].second};
		uint32_t colorToMatch = 0;
		if (neighbourPos.x < 0 || neighbourPos.x >= m_boardSize.width || neighbourPos.y < 0 || neighbourPos.y >= m_boardSize.height) {
			colorToMatch = board.getDefaultEdgeColor();
		} else {
			uint32_t linePos = neighbourPos.x + neighbourPos.y * m_boardSize.width;
			uint32_t childPiece = child[linePos].first;
			if (childPiece != 0) {
				colorToMatch = board.getPiece(childPiece).getEdges()[(i + 2) % 4];
			}
		}
		colors[i] = colorToMatch;
	}
	uint32_t bestScore = 0;
	std::vector<uint32_t> bestPieces;
	for (uint32_t piece : piecesAvailable) {
		uint32_t score = 0;
		for (uint32_t i = 0; i < 4; ++i) {
			if (colors[i] == 0)
				++score;
			if (colors[i] == board.getPiece(piece).getEdges()[i])
				++score;
		}
		if (score > bestScore) {
			bestPieces.clear();
			bestPieces.push_back(piece);
			bestScore = score;
		} else if (score == bestScore) {
			bestPieces.push_back(piece);
		}
	}
	if (bestPieces.empty())
		return 0;
	return bestPieces[rand() % bestPieces.size()];
}

std::vector<uint32_t> etm::SholomonGeneticSolver::getNeighbours(const std::vector<std::pair<uint32_t, uint32_t>> &board, uint32_t pos) {
	Position2D pos2D{pos % this->m_boardSize.width, pos / this->m_boardSize.height};
	static const std::array<std::pair<short, short>, 4> iToMod = {
			std::make_pair(0, -1),
			std::make_pair(1, 0),
			std::make_pair(0, 1),
			std::make_pair(-1, 0),
	};

	std::vector<uint32_t> neighbours;
	for (auto const& mod : iToMod) {
		Position2D neighbourPos{pos2D.x + mod.first, pos2D.y + mod.second};
		if (neighbourPos.x < 0 || neighbourPos.x >= m_boardSize.width || neighbourPos.y < 0 || neighbourPos.y >= m_boardSize.height) {
			neighbours.emplace_back(0);
			continue;
		}
		uint32_t linePos = neighbourPos.x + neighbourPos.y * m_boardSize.width;
		neighbours.emplace_back(board[linePos].first);
	}
	return neighbours;
}

uint32_t etm::SholomonGeneticSolver::matchingNeighboursComparison(const std::vector<std::pair<uint32_t, uint32_t>> &board, const std::vector<uint32_t> &neighbours) {
	for (uint32_t pos = 0; pos < board.size(); ++pos) {
		auto compNeighbours = getNeighbours(board, pos);
		bool valid = true;
		for (uint32_t i = 0; i < neighbours.size(); ++i) {
			if (compNeighbours[i] != neighbours[i])
				valid = false;
		}
		if (valid)
			return board[pos].first;
	}
	return 0;
}
