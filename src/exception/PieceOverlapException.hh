//
// Created by Guillaume on 06/06/2019.
//


#pragma once
#ifndef ETERNITYII_PIECEOVERLAPEXCEPTION_HH
#define ETERNITYII_PIECEOVERLAPEXCEPTION_HH

#include "GameException.hh"

namespace etm {
	/**
	 * Exception class related to all overlapping between two pieces operations.
	 *
	 * @inherit GameException
	 * @author Guillaume Julien
	 * @date 06 June 2019
	 */
	class PieceOverlapException : virtual public GameException {
	public:
		/**
		 * Constructor calling to GameException constructor
		 *
		 * @param message Message to be set, with a default value
		 */
		explicit PieceOverlapException(const std::string &message = "An action implying a piece overlap with another piece."); //TODO: add overlapping information, such as position and pieces id.

		/**
		 * Default destructor
		 */
		~PieceOverlapException() noexcept override = default;
	};
}

#endif //ETERNITYII_PIECEOVERLAPEXCEPTION_HH
