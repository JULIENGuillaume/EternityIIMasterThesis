//
// Created by Guillaume on 06/06/2019.
//

#include "GameException.hh"

etm::GameException::GameException(std::string const& message) : m_message(message) {}

const char *etm::GameException::what() const {
	return m_message.c_str();
}
