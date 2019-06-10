//
// Created by Guillaume on 10/06/2019.
//

#include "SquarePiece.hh"

etm::SquarePiece::SquarePiece(uint32_t id, std::array<uint32_t, 4> const &edges) : m_id(id), m_edges(edges.begin(), edges.end()) {}

uint32_t etm::SquarePiece::getId() const {
	return this->m_id;
}

uint32_t etm::SquarePiece::getPieceDimension() const {
	return 4;
}

const std::vector<uint32_t> &etm::SquarePiece::getEdges() const {
	return this->m_edges;
}
