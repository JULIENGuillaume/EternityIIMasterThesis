//
// Created by Guillaume on 03/06/2019.
//


#pragma once
#ifndef ETERNITYII_IPIECE_HH
#define ETERNITYII_IPIECE_HH

#include <cstdint>
#include <vector>

namespace etm {
	/**
	 * Interface abstracting the logic of a piece. It allow to get piece information.
	 *
	 * @author Guillaume Julien
	 * @date 04 June 2019
	 *
	 * @interface IPiece IPiece.hh "IPiece.hh"
	 */
	class IPiece {
	public:
		/**
		 * Virtual default destructor.
		 */
		virtual ~IPiece() = default;

		/**
		 * Get the id of the piece. Is always >= 1.
		 *
		 * @return An uint32_t representing the id of the piece
		 */
		virtual uint32_t getId() const = 0;

		/**
 		 * Get the dimension of the piece, which represent the number of  edges that connect with neighbours (default should be 4).
 		 *
 		 * @return An uint32_t representing the dimension of the piece
 		 */
		virtual uint32_t getPieceDimension() const = 0;

		/**
		 * Get the ids of the edges of the piece. The vector is of the size returned by getPieceDimension().
		 * The edges are ordered clockwise.
		 *
		 * @return A vector of uint32_t representing the edges of the piece
		 */
		virtual std::vector<uint32_t> const& getEdges() const = 0;
	};
}

#endif //ETERNITYII_IPIECE_HH
