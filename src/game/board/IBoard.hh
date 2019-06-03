//
// Created by Guillaume on 03/06/2019.
//


#pragma once
#ifndef ETERNITYII_IBOARD_HH
#define ETERNITYII_IBOARD_HH

#include <Size2D.hh>

namespace etm {
	/**
	 * Interface abstracting the logic of the board. It allows to retrieve information,
	 * play the game, add state observers and evaluate the final result.
	 */
	class IBoard {
	public:
		/**
		 * Virtual default destructor.
		 */
		virtual ~IBoard() = default;

		/**
		 * Get the size of the board, in a width and height format (default should be 16x16).
		 *
		 * @return A Size2D class containing the size information of the current board
		 */
		virtual Size2D const& getSize() const = 0;

		/**
		 * Get the dimension of the pieces of the board, which represent the number of  edges that connect with neighbours (default should be 4).
		 *
		 * @return An uint32_t representing the dimension of the pieces
		 */
		virtual uint32_t getPieceDimension() const = 0;
	};
}

#endif //ETERNITYII_IBOARD_HH
