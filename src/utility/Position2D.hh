//
// Created by Guillaume on 06/06/2019.
//

#ifndef ETERNITYII_POSITION2D_HH
#define ETERNITYII_POSITION2D_HH

#include <cinttypes>

namespace etm {
	/**
	 * Represent a 2D discrete position by its x and y coordinate.
	 *
	 * @author Guillaume Julien
	 * @date 06 June 2019
	 */
	struct Position2D {
		/**
		 * The x component of the position.
		 */
		uint32_t x = 0;

		/**
		 * The y component of the position.
		 */
		uint32_t y = 0;
	};
}
#endif //ETERNITYII_POSITION2D_HH
