//
// Created by Guillaume Julien on 09/08/2019.
//


#include <NonExistingPieceException.hh>
#include <OutOfBoardException.hh>
#include <PieceOverlapException.hh>
#include <BoardValidationException.hh>
#include <iostream>
#include "DynamicSizedBoard.hh"

const uint32_t etm::DynamicSizedBoard::boardEdgesColor = 1;

etm::DynamicSizedBoard::DynamicSizedBoard(const std::vector<SquarePiece> &pieceSet, const Size2D& size) : m_size(size), m_pieceSet(pieceSet.begin(), pieceSet.end()) {
	m_totalSize = m_size.height * m_size.width;
	m_idToRotation.reserve(m_totalSize);
	m_idToPosition.reserve(m_totalSize);
	m_playedPieces.reserve(m_totalSize);
	m_remainingPieces.reserve(m_totalSize);
	for (auto const &piece : m_pieceSet) {
		m_idToPieces.insert({piece.getId(), piece});
		m_remainingPieces.insert(piece.getId());
	}
	this->m_board.resize(m_totalSize, 0);
}

const etm::Size2D &etm::DynamicSizedBoard::getSize() const {
	return m_size;
}

uint32_t etm::DynamicSizedBoard::getPieceDimension() const {
	return 4;
}

const std::vector<uint32_t> &etm::DynamicSizedBoard::getCurrentBoardPieces() const {
	return m_board;
}

const std::unordered_set<uint32_t> &etm::DynamicSizedBoard::getPlayedPieces() const {
	return m_playedPieces;
}

const std::unordered_map<uint32_t, uint32_t> &etm::DynamicSizedBoard::getPlayedPiecesPosition() const {
	return m_idToPosition;
}

const std::unordered_set<uint32_t> &etm::DynamicSizedBoard::getRemainingPieces() const {
	return m_remainingPieces;
}

const std::unordered_map<uint32_t, uint32_t> &etm::DynamicSizedBoard::getPiecesRotation() const {
	return m_idToRotation;
}

const etm::IPiece &etm::DynamicSizedBoard::getPiece(uint32_t pieceId) const {
	if (m_idToPieces.find(pieceId) == m_idToPieces.end())
		throw NonExistingPieceException();
	return m_idToPieces.at(pieceId);
}

const std::unordered_map<uint32_t, const etm::IPiece &> &etm::DynamicSizedBoard::getAllPieces() const {
	return m_idToPieces;
}

uint32_t etm::DynamicSizedBoard::placePiece(uint32_t pieceId, const etm::Position2D &pos, bool forceRemove) {
	if (pos.x >= m_size.width || pos.y >= m_size.height)
		throw OutOfBoardException();
	return placePiece(pieceId, getLinearPosition(pos), forceRemove);
}

uint32_t etm::DynamicSizedBoard::placePiece(uint32_t pieceId, uint32_t pos, bool forceRemove) {
	if (pos >= m_totalSize)
		throw OutOfBoardException();
	if (this->m_idToPieces.find(pieceId) == this->m_idToPieces.end())
		throw NonExistingPieceException();
	if (this->m_board[pos] != 0) {
		if (!forceRemove)
			throw PieceOverlapException();
		removePiece(pos);
	}
	this->m_board[pos] = pieceId;
	this->m_playedPieces.insert(pieceId);
	this->m_remainingPieces.erase(pieceId);
	this->m_idToPosition.insert({pieceId, pos});
	this->m_idToRotation.insert({pieceId, 0});
	return getMismatchScore(pos);
}

void etm::DynamicSizedBoard::removePiece(const etm::Position2D &pos) {
	if (pos.x >= m_size.width || pos.y >= m_size.height)
		throw OutOfBoardException();
	removePiece(getLinearPosition(pos));
}

void etm::DynamicSizedBoard::removePiece(uint32_t pos) {
	if (pos >= m_totalSize)
		throw OutOfBoardException();
	uint32_t pieceId = this->m_board[pos];
	this->m_board[pos] = 0;
	this->m_playedPieces.erase(pieceId);
	this->m_remainingPieces.insert(pieceId);
	this->m_idToPosition.erase(pieceId);
	this->m_idToRotation.erase(pieceId);
}

uint32_t etm::DynamicSizedBoard::rotatePiece(const etm::Position2D &pos, uint32_t rotation) {
	if (pos.x >= m_size.width || pos.y >= m_size.height)
		throw OutOfBoardException();
	return rotatePiece(getLinearPosition(pos), rotation);
}

uint32_t etm::DynamicSizedBoard::rotatePiece(uint32_t pos, uint32_t rotation) {
	if (pos >= m_totalSize)
		throw OutOfBoardException();
	if (this->m_board[pos] == 0)
		throw NonExistingPieceException("There is no piece in this position on the board.");
	uint32_t pieceId = this->m_board[pos];
	this->m_idToRotation[pieceId] = (this->m_idToRotation[pieceId] + rotation) % 4;
	return getMismatchScore(pos);
}

uint32_t etm::DynamicSizedBoard::getLinearPosition(const etm::Position2D &pos) const {
	return pos.x + pos.y * m_size.width;
}

std::vector<uint32_t> etm::DynamicSizedBoard::getRotatedEdges(const etm::Position2D &pos) const {
	if (pos.x >= m_size.width || pos.y >= m_size.height)
		throw OutOfBoardException();
	return getRotatedEdges(getLinearPosition(pos));
}

std::vector<uint32_t> etm::DynamicSizedBoard::getRotatedEdges(uint32_t const &pos) const {
	if (pos >= m_totalSize)
		throw OutOfBoardException();
	std::array<uint32_t, 4> array = {0, 0, 0, 0};
	uint32_t piecedId = this->m_board[pos];
	if (piecedId != 0) {
		uint32_t rotation = this->m_idToRotation.find(piecedId) != this->m_idToRotation.end() ? this->m_idToRotation.at(piecedId) : 0; //fixme: invalid key sometime arise ?
		/*uint32_t rotation;
		try {
			rotation = this->m_idToRotation.at(piecedId);
		} catch (std::out_of_range &) {
			rotation = 0;
		}*/

		auto const &edges = this->m_idToPieces.at(piecedId).getEdges();
		for (uint32_t idx = 0; idx < 4; ++idx) {
			array[(idx + rotation) % 4] = edges[idx];
		}
	}
	return std::vector<uint32_t>(array.begin(), array.end());
}

void etm::DynamicSizedBoard::validate() const {
	if (this->m_pieceSet.size() != m_totalSize)
		throw BoardValidationException("The number of pieces doesn't match the size of the board.");
	if (this->m_pieceSet.size() != this->m_idToPieces.size())
		throw BoardValidationException("There are duplicate pieces with common ids.");
	std::unordered_map<uint32_t, uint32_t> edgeColorOccurrences;
	for (auto const &piece : this->m_pieceSet) {
		if (piece.getId() == 0)
			throw BoardValidationException("Error: you can't have any piece using the reserved id 0");
		auto const &edges = piece.getEdges();
		for (auto const &edge : edges) {
			if (edge == 0)
				throw BoardValidationException("Error: you can't have any edges using the reserved id 0");
			++edgeColorOccurrences[edge];
		}
	}
	if (edgeColorOccurrences[DynamicSizedBoard::boardEdgesColor] < 2 * this->m_size.width + 2 * this->m_size.height)
		throw BoardValidationException("There isn't enough edges to match the border color " + std::to_string(edgeColorOccurrences[DynamicSizedBoard::boardEdgesColor])  +" of " + std::to_string(DynamicSizedBoard::boardEdgesColor));
	for (auto const& edge : edgeColorOccurrences) {
		if (edge.second % 2 != 0)
			throw BoardValidationException("The edges need to be even matched");
	}
}

uint32_t etm::DynamicSizedBoard::getDefaultEdgeColor() const {
	return DynamicSizedBoard::boardEdgesColor;
}

uint32_t etm::DynamicSizedBoard::getMismatchScore(uint32_t pos) {
	auto edges = getRotatedEdges(pos);
	uint32_t mismatchScore = 0;
	Position2D currentPos{pos % m_size.width, pos / m_size.width};
	for (uint8_t i = 0; i < 4; ++i) {
		if ((i == 0 && currentPos.y == 0) || (i == 1 && currentPos.x == m_size.width - 1) ||
		    (i == 2 && currentPos.y == m_size.height - 1) || (i == 3 && currentPos.x == 0)) {
			if (edges[i] != DynamicSizedBoard::boardEdgesColor)
				++mismatchScore;
			continue;
		}
		static const std::array<std::pair<short, short>, 4> iToMod = {
				std::make_pair(0, -1),
				std::make_pair(1, 0),
				std::make_pair(0, 1),
				std::make_pair(-1, 0),
		};
		Position2D nextPos{currentPos.x + iToMod[i].first, currentPos.y + iToMod[i].second};
		uint32_t oppositeColor = getRotatedEdges(nextPos)[(i + 2) % 4];
		if (oppositeColor != 0 && oppositeColor != edges[i])
			++mismatchScore;
	}
	return mismatchScore;
}