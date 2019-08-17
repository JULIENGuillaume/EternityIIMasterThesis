//
// Created by Guillaume on 10/06/2019.
//


#pragma once
#ifndef ETERNITYII_SQUAREPIECE_HH
#define ETERNITYII_SQUAREPIECE_HH

#include <array>
#include "IPiece.hh"

namespace etm {
	class SquarePiece : public IPiece {
	public:
		explicit SquarePiece(uint32_t id, std::array<uint32_t, 4> const &edges);
		uint32_t getId() const override;
		uint32_t getPieceDimension() const override;
		const std::vector<uint32_t> &getEdges() const override;
	public:
		void colorPieceEdge(uint32_t edge, uint32_t color);
		void setId(uint32_t id);
	protected:
		uint32_t m_id;
		std::vector<uint32_t> m_edges;
	};
}

#endif //ETERNITYII_SQUAREPIECE_HH
