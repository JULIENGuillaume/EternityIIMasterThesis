//
// Created by Guillaume on 11/06/2019.
//

#include <NonExistingPieceException.hh>
#include <OutOfBoardException.hh>
#include <PieceOverlapException.hh>
#include <BoardValidationException.hh>
#include <iostream>
#include "FixedBoard4x4ForSquarePieces.hh"

const uint32_t etm::FixedBoard4x4ForSquarePieces::boardEdgesColor = 1;

etm::FixedBoard4x4ForSquarePieces::FixedBoard4x4ForSquarePieces(const std::array<SquarePiece, 16> &pieceSet) : m_pieceSet(pieceSet.begin(), pieceSet.end()) {
	for (auto const &piece : m_pieceSet) {
		m_idToPieces.insert({piece.getId(), piece});
		m_idToRotation.reserve(16);
		m_idToPosition.reserve(16);
		m_playedPieces.reserve(16);
		m_remainingPieces.reserve(16);
		m_remainingPieces.insert(piece.getId());
	}
}

const etm::Size2D &etm::FixedBoard4x4ForSquarePieces::getSize() const {
	return m_size;
}

uint32_t etm::FixedBoard4x4ForSquarePieces::getPieceDimension() const {
	return 4;
}

const std::vector<uint32_t> &etm::FixedBoard4x4ForSquarePieces::getCurrentBoardPieces() const {
	return m_board;
}

const std::unordered_set<uint32_t> &etm::FixedBoard4x4ForSquarePieces::getPlayedPieces() const {
	return m_playedPieces;
}

const std::unordered_map<uint32_t, uint32_t> &etm::FixedBoard4x4ForSquarePieces::getPlayedPiecesPosition() const {
	return m_idToPosition;
}

const std::unordered_set<uint32_t> &etm::FixedBoard4x4ForSquarePieces::getRemainingPieces() const {
	return m_remainingPieces;
}

const std::unordered_map<uint32_t, uint32_t> &etm::FixedBoard4x4ForSquarePieces::getPiecesRotation() const {
	return m_idToRotation;
}

const etm::IPiece &etm::FixedBoard4x4ForSquarePieces::getPiece(uint32_t pieceId) const {
	if (m_idToPieces.find(pieceId) == m_idToPieces.end())
		throw NonExistingPieceException();
	return m_idToPieces.at(pieceId);
}

const std::unordered_map<uint32_t, const etm::IPiece &> &etm::FixedBoard4x4ForSquarePieces::getAllPieces() const {
	return m_idToPieces;
}

uint32_t etm::FixedBoard4x4ForSquarePieces::placePiece(uint32_t pieceId, const etm::Position2D &pos, bool forceRemove) {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	return placePiece(pieceId, getLinearPosition(pos), forceRemove);
}

uint32_t etm::FixedBoard4x4ForSquarePieces::placePiece(uint32_t pieceId, uint32_t pos, bool forceRemove) {
	if (pos >= 16)
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

void etm::FixedBoard4x4ForSquarePieces::removePiece(const etm::Position2D &pos) {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	removePiece(getLinearPosition(pos));
}

void etm::FixedBoard4x4ForSquarePieces::removePiece(uint32_t pos) {
	if (pos >= 16)
		throw OutOfBoardException();
	uint32_t pieceId = this->m_board[pos];
	this->m_board[pos] = 0;
	this->m_playedPieces.erase(pieceId);
	this->m_remainingPieces.insert(pieceId);
	this->m_idToPosition.erase(pieceId);
	this->m_idToRotation.erase(pieceId);
}

uint32_t etm::FixedBoard4x4ForSquarePieces::rotatePiece(const etm::Position2D &pos, uint32_t rotation) {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	return rotatePiece(getLinearPosition(pos), rotation);
}

uint32_t etm::FixedBoard4x4ForSquarePieces::rotatePiece(uint32_t pos, uint32_t rotation) {
	if (pos >= 16)
		throw OutOfBoardException();
	if (this->m_board[pos] == 0)
		throw NonExistingPieceException("There is no piece in this position on the board.");
	uint32_t pieceId = this->m_board[pos];
	this->m_idToRotation[pieceId] = (this->m_idToRotation[pieceId] + rotation) % 4;
	return getMismatchScore(pos);
}

uint32_t etm::FixedBoard4x4ForSquarePieces::getLinearPosition(const etm::Position2D &pos) const {
	return pos.x + pos.y * 4;
}

std::vector<uint32_t> etm::FixedBoard4x4ForSquarePieces::getRotatedEdges(const etm::Position2D &pos) const {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	return getRotatedEdges(getLinearPosition(pos));
}

std::vector<uint32_t> etm::FixedBoard4x4ForSquarePieces::getRotatedEdges(uint32_t const &pos) const {
	if (pos >= 16)
		throw OutOfBoardException();
	std::array<uint32_t, 4> array = {0, 0, 0, 0};
	uint32_t piecedId = this->m_board[pos];
	if (piecedId != 0) {
		uint32_t rotation = this->m_idToRotation.find(piecedId) != this->m_idToRotation.end() ? this->m_idToRotation.at(piecedId) : 0; //fixme: invalid key sometime arise ?
		auto const &edges = this->m_idToPieces.at(piecedId).getEdges();
		for (uint32_t idx = 0; idx < 4; ++idx) {
			array[(idx + rotation) % 4] = edges[idx];
		}
	}
	return std::vector<uint32_t>(array.begin(), array.end());
}

void etm::FixedBoard4x4ForSquarePieces::validate() const {
	if (this->m_pieceSet.size() != 16)
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
	if (edgeColorOccurrences[FixedBoard4x4ForSquarePieces::boardEdgesColor] < 16)
		throw BoardValidationException("There isn't enough edges to match the border color " + std::to_string(edgeColorOccurrences[FixedBoard4x4ForSquarePieces::boardEdgesColor])  +" of " + std::to_string(FixedBoard4x4ForSquarePieces::boardEdgesColor));
	for (auto const& edge : edgeColorOccurrences) {
		if (edge.second % 2 != 0)
			throw BoardValidationException("The edges need to be even matched");
	}
}

uint32_t etm::FixedBoard4x4ForSquarePieces::getDefaultEdgeColor() const {
	return FixedBoard4x4ForSquarePieces::boardEdgesColor;
}

uint32_t etm::FixedBoard4x4ForSquarePieces::getMismatchScore(uint32_t pos) {
	auto edges = getRotatedEdges(pos);
	uint32_t mismatchScore = 0;
	Position2D currentPos{pos % 4, pos / 4};
	for (uint8_t i = 0; i < 4; ++i) {
		if ((i == 0 && currentPos.y == 0) || (i == 1 && currentPos.x == m_size.width - 1) ||
		    (i == 2 && currentPos.y == m_size.height - 1) || (i == 3 && currentPos.x == 0)) {
			if (edges[i] != FixedBoard4x4ForSquarePieces::boardEdgesColor)
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
