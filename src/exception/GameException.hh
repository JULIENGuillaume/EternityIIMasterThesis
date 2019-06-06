//
// Created by Guillaume on 06/06/2019.
//


#pragma once
#ifndef ETERNITYII_GAMEEXCEPTION_HH
#define ETERNITYII_GAMEEXCEPTION_HH

#include <exception>
#include <string>

namespace etm {
	/**
	 * Base class for all exception related to the game
	 *
	 * @author Guillaume Julien
	 * @date 06 June 2019
	 */
	class GameException : virtual public std::exception {
	public:
		/**
		 * Constructor setting the message as an std::string.
		 *
		 * @param message Message to describe the exception.
		 */
		explicit GameException(std::string const& message);

		/**
		 * Default destructor.
		 */
		~GameException() noexcept override = default;

		/**
		 * Override of std::exception::what() to adapt to std::string message.
		 *
		 * @return A const char* that contain the description of the problem.
		 */
		const char *what() const noexcept override;

	protected:
		/**
		 * The message to be displayed, set in the constructor.
		 */
		std::string const& m_message;
	};
}

#endif //ETERNITYII_GAMEEXCEPTION_HH
