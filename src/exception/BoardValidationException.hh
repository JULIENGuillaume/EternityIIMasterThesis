//
// Created by Guillaume on 13/06/2019.
//


#pragma once
#ifndef ETERNITYII_BOARDVALIDATIONEXCEPTION_HH
#define ETERNITYII_BOARDVALIDATIONEXCEPTION_HH

#include "GameException.hh"

namespace etm {
	class BoardValidationException : public virtual GameException {
	public:
		/**
		 * Constructor calling to GameException constructor
		 *
		 * @param message Message to be set, with a default value
		 */
		explicit BoardValidationException(const std::string &message = "The board is invalid.");

		/**
 		 * Default destructor
 		 */
		~BoardValidationException() noexcept override = default;
	};
}

#endif //ETERNITYII_BOARDVALIDATIONEXCEPTION_HH
