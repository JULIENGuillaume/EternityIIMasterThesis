//
// Created by Guillaume on 06/06/2019.
//


#pragma once
#ifndef ETERNITYII_NONEXISTINGPIECEEXCEPTION_HH
#define ETERNITYII_NONEXISTINGPIECEEXCEPTION_HH

#include "GameException.hh"

namespace etm {
	/**
	 * Exception class related to all invalid piece id operations.
	 *
	 * @author Guillaume Julien
	 * @date 06 June 2019
	 */
	class NonExistingPieceException : virtual public GameException {
	public:
		/**
		 * Constructor calling to GameException constructor
		 *
		 * @param message Message to be set, with a default value
		 */
		explicit NonExistingPieceException(const std::string &message = "An action implying a non existing piece took place."); //TODO: add piece information

		/**
		 * Default destructor
		 */
		~NonExistingPieceException() noexcept override = default;
	};
}

#endif //ETERNITYII_NONEXISTINGPIECEEXCEPTION_HH
