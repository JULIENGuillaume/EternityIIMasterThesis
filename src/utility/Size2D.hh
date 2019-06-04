//
// Created by Guillaume on 03/06/2019.
//


#pragma once
#ifndef ETERNITYII_SIZE2D_HH
#define ETERNITYII_SIZE2D_HH

#include <cinttypes>

namespace etm {
	/**
	 * Represent a 2D discrete size by its width and its length.
	 * Allow for basic helper operation, such as getting the area.
	 *
	 * @author Guillaume Julien
	 * @date 04 June 2019
	 */
	struct Size2D {
		/**
		 * The height component of the size, as an unsigned int.
		 */
		uint32_t height = 0;

		/**
		 * The width component of the size, as an unsigned int.
		 */
		uint32_t width = 0;
	};
}

#endif //ETERNITYII_SIZE2D_HH
