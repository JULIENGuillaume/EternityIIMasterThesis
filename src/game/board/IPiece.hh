//
// Created by Guillaume on 03/06/2019.
//


#pragma once
#ifndef ETERNITYII_IPIECE_HH
#define ETERNITYII_IPIECE_HH

#include <cstdint>

namespace etm {
	/**
	 * Interface abstracting the logic of a piece. It allow to get piece information.
	 *
	 * @author Guillaume Julien
	 * @date 04 June 2019
	 */
	class IPiece {
	public:
		/**
		 * Virtual default destructor.
		 */
		virtual ~IPiece() = default;

		/**
 		 * Get the dimension of the piece, which represent the number of  edges that connect with neighbours (default should be 4).
 		 *
 		 * @return An uint32_t representing the dimension of the pieces
 		 */
		virtual uint32_t getPieceDimension() const = 0;
	};
}

#endif //ETERNITYII_IPIECE_HH
