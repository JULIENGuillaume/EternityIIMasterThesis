//
// Created by Guillaume on 12/06/2019.
//


#pragma once
#ifndef ETERNITYII_TEXTUALDISPLAY_HH
#define ETERNITYII_TEXTUALDISPLAY_HH

#include <IBoard.hh>
#include "IDisplay.hh"

namespace etm {
	class TextualDisplay : public IDisplay {
	public:
		explicit TextualDisplay(IBoard const& board);
		void refresh() const override;
	protected:
		IBoard const& m_board;
	};
}

#endif //ETERNITYII_TEXTUALDISPLAY_HH
