//
// Created by Guillaume on 10/06/2019.
//

#include "SquarePiece.hh"
#include "GameException.hh"

etm::SquarePiece::SquarePiece(uint32_t id, std::array<uint32_t, 4> const &edges) : m_id(id), m_edges(edges.begin(), edges.end()) {
	if (m_id == 0)
		throw GameException("Id of a piece must be different than 0");
}

uint32_t etm::SquarePiece::getId() const {
	return this->m_id;
}

uint32_t etm::SquarePiece::getPieceDimension() const {
	return 4;
}

const std::vector<uint32_t> &etm::SquarePiece::getEdges() const {
	return this->m_edges;
}

void etm::SquarePiece::colorPieceEdge(uint32_t edge, uint32_t color) {
	this->m_edges[edge] = color;
}

void etm::SquarePiece::setId(uint32_t id) {
	this->m_id = id;
}
