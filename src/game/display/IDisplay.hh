//
// Created by Guillaume on 03/06/2019.
//


#pragma once
#ifndef ETERNITYII_IDISPLAY_HH
#define ETERNITYII_IDISPLAY_HH

namespace etm {
	/**
	 * Interface abstracting the display of the board. It allows to
	 * push information to an output and trigger a refresh of it.
	 *
	 * @author Guillaume Julien
	 * @date 04 June 2019
	 *
	 * @interface IDisplay IDisplay.hh "IDisplay.hh"
	 */
	class IDisplay {
	public:
		virtual ~IDisplay() = default;
		virtual void refresh() const = 0;
	};
}

#endif //ETERNITYII_IDISPLAY_HH
