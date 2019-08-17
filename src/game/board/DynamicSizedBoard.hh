//
// Created by Guillaume Julien on 09/08/2019.
//

#ifndef ETERNITYII_DYNAMICSIZEDBOARD_HH
#define ETERNITYII_DYNAMICSIZEDBOARD_HH

#include "IBoard.hh"
#include "SquarePiece.hh"

namespace etm {
	class DynamicSizedBoard : public IBoard {
	public:
		explicit DynamicSizedBoard(const std::vector<SquarePiece> &pieceSet, Size2D const& size);

		const Size2D &getSize() const override;
		uint32_t getPieceDimension() const override;
		const std::vector<uint32_t> &getCurrentBoardPieces() const override;
		const std::unordered_set<uint32_t> &getPlayedPieces() const override;
		const std::unordered_map<uint32_t, uint32_t> &getPlayedPiecesPosition() const override;
		const std::unordered_set<uint32_t> &getRemainingPieces() const override;
		const std::unordered_map<uint32_t, uint32_t> &getPiecesRotation() const override;
		const IPiece &getPiece(uint32_t pieceId) const override;
		const std::unordered_map<uint32_t, const IPiece &> &getAllPieces() const override;
		uint32_t placePiece(uint32_t pieceId, Position2D const &pos, bool forceRemove) override;
		uint32_t placePiece(uint32_t pieceId, uint32_t pos, bool forceRemove) override;
		void removePiece(Position2D const &pos) override;
		void removePiece(uint32_t pos) override;
		uint32_t rotatePiece(Position2D const &pos, uint32_t rotation) override;
		uint32_t rotatePiece(uint32_t pos, uint32_t rotation) override;
		uint32_t getLinearPosition(Position2D const &pos) const override;
		std::vector<uint32_t> getRotatedEdges(Position2D const &pos) const override;
		std::vector<uint32_t> getRotatedEdges(uint32_t const &pos) const override;
		void validate() const override;
		uint32_t getDefaultEdgeColor() const override;

	protected:
		uint32_t getMismatchScore(uint32_t pos);

	public:
		static const uint32_t boardEdgesColor;

	protected:
		Size2D m_size;
		uint32_t m_totalSize;
		std::vector<SquarePiece> m_pieceSet;
		std::vector<uint32_t> m_board;
	protected:
		std::unordered_map<uint32_t, IPiece const &> m_idToPieces;
		std::unordered_map<uint32_t, uint32_t> m_idToRotation;
		std::unordered_map<uint32_t, uint32_t> m_idToPosition;
		std::unordered_set<uint32_t> m_playedPieces;
		std::unordered_set<uint32_t> m_remainingPieces;
	};
}

#endif //ETERNITYII_DYNAMICSIZEDBOARD_HH
