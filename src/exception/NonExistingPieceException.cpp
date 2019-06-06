//
// Created by Guillaume on 06/06/2019.
//

#include "NonExistingPieceException.hh"

etm::NonExistingPieceException::NonExistingPieceException(const std::string &message) : GameException(message) {}
