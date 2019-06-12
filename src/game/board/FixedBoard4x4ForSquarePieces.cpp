//
// Created by Guillaume on 11/06/2019.
//

#include <NonExistingPieceException.hh>
#include <OutOfBoardException.hh>
#include <PieceOverlapException.hh>
#include "FixedBoard4x4ForSquarePieces.hh"

etm::FixedBoard4x4ForSquarePieces::FixedBoard4x4ForSquarePieces(const std::array<SquarePiece, 16> &pieceSet) : m_pieceSet(pieceSet.begin(), pieceSet.end()) {
	for (auto const& piece : m_pieceSet) {
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

void etm::FixedBoard4x4ForSquarePieces::placePiece(uint32_t pieceId, const etm::Position2D &pos, bool forceRemove) {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	placePiece(pieceId, pos.x + pos.y * 4, forceRemove);
}

void etm::FixedBoard4x4ForSquarePieces::placePiece(uint32_t pieceId, uint32_t pos, bool forceRemove) {
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
}

void etm::FixedBoard4x4ForSquarePieces::removePiece(const etm::Position2D &pos) {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	removePiece(pos.x + pos.y * 4);
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

void etm::FixedBoard4x4ForSquarePieces::rotatePiece(const etm::Position2D &pos, uint32_t rotation) {
	if (pos.x >= 4 || pos.y >= 4)
		throw OutOfBoardException();
	rotatePiece(pos.x + pos.y * 4, rotation);
}

void etm::FixedBoard4x4ForSquarePieces::rotatePiece(uint32_t pos, uint32_t rotation) {
	if (pos >= 16)
		throw OutOfBoardException();
	if (this->m_board[pos] == 0)
		throw NonExistingPieceException("There is no piece in this position on the board.");
	uint32_t pieceId = this->m_board[pos];
	this->m_idToRotation[pieceId] = (this->m_idToRotation[pieceId] + rotation) % 4;
}
