//
// Created by Guillaume on 06/06/2019.
//


#pragma once
#ifndef ETERNITYII_OUTOFBOARDEXCEPTION_HH
#define ETERNITYII_OUTOFBOARDEXCEPTION_HH

#include "GameException.hh"

namespace etm {
	/**
	 * Exception class related to all out of board errors.
	 *
	 * @inherit GameException
	 * @author Guillaume Julien
	 * @date 06 June 2019
	 */
	class OutOfBoardException : virtual public GameException {
	public:
		/**
		 * Constructor calling to GameException constructor
		 *
		 * @param message Message to be set, with a default value
		 */
		explicit OutOfBoardException(const std::string &message = "An action was done out of the board."); //TODO: add board size and precise out of bound information

		/**
		 * Default destructor
		 */
		~OutOfBoardException() noexcept override = default;
	};
}

#endif //ETERNITYII_OUTOFBOARDEXCEPTION_HH
