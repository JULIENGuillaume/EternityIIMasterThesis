//
// Created by Guillaume on 06/06/2019.
//

#include <iostream>
#include <utility>
#include "GameException.hh"

etm::GameException::GameException(std::string const &message) : runtime_error(message), m_message(message) {}

const char *etm::GameException::what() const noexcept {
	return m_message.c_str();
}
