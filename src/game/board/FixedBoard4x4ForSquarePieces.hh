//
// Created by Guillaume on 11/06/2019.
//


#pragma once
#ifndef ETERNITYII_FIXEDBOARD4X4FORSQUAREPIECES_HH
#define ETERNITYII_FIXEDBOARD4X4FORSQUAREPIECES_HH

#include "IBoard.hh"
#include "SquarePiece.hh"

namespace etm {
	class FixedBoard4x4ForSquarePieces : public IBoard {
	public:
		explicit FixedBoard4x4ForSquarePieces(std::array<SquarePiece, 16> const &pieceSet);

		const Size2D &getSize() const override;
		uint32_t getPieceDimension() const override;
		const std::vector<uint32_t> &getCurrentBoardPieces() const override;
		const std::unordered_set<uint32_t> &getPlayedPieces() const override;
		const std::unordered_map<uint32_t, uint32_t> &getPlayedPiecesPosition() const override;
		const std::unordered_set<uint32_t> &getRemainingPieces() const override;
		const std::unordered_map<uint32_t, uint32_t> &getPiecesRotation() const override;
		const IPiece &getPiece(uint32_t pieceId) const override;
		const std::unordered_map<uint32_t, const IPiece &> &getAllPieces() const override;
		void placePiece(uint32_t pieceId, Position2D const &pos, bool forceRemove) override;
		void placePiece(uint32_t pieceId, uint32_t pos, bool forceRemove) override;
		void removePiece(Position2D const &pos) override;
		void removePiece(uint32_t pos) override;
		void rotatePiece(Position2D const &pos, uint32_t rotation) override;
		void rotatePiece(uint32_t pos, uint32_t rotation) override;
		uint32_t getLinearPosition(Position2D const &pos) const override;
		std::vector<uint32_t> getRotatedEdges(Position2D const &pos) const override;
		std::vector<uint32_t> getRotatedEdges(uint32_t const &pos) const override;
		void validate() const override;

	public:
		static const uint32_t boardEdgesColor;

	protected:
		Size2D m_size = {4, 4};
		std::vector<SquarePiece> m_pieceSet;
		std::vector<uint32_t> m_board = {
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
		};
	protected:
		std::unordered_map<uint32_t, IPiece const &> m_idToPieces;
		std::unordered_map<uint32_t, uint32_t> m_idToRotation;
		std::unordered_map<uint32_t, uint32_t> m_idToPosition;
		std::unordered_set<uint32_t> m_playedPieces;
		std::unordered_set<uint32_t> m_remainingPieces;
	};
}

#endif //ETERNITYII_FIXEDBOARD4X4FORSQUAREPIECES_HH
