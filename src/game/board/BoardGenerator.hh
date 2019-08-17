//
// Created by Guillaume Julien on 09/08/2019.
//

#ifndef ETERNITYII_BOARDGENERATOR_HH
#define ETERNITYII_BOARDGENERATOR_HH

#include <memory>
#include "IBoard.hh"

namespace etm {
	class BoardGenerator {
	public:
		static std::unique_ptr<IBoard> generateBoard(uint32_t size, uint32_t numberOfInternalColors, uint32_t borderColor = 1);
	};
}

#endif //ETERNITYII_BOARDGENERATOR_HH
