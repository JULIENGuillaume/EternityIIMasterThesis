//
// Created by Guillaume on 17/06/2019.
//


#pragma once
#ifndef ETERNITYII_SCOREREPORT_HH
#define ETERNITYII_SCOREREPORT_HH

#include <cstdint>

namespace etm {
	struct ScoreReport {
		uint32_t maxScore = 0;
		uint32_t cumulativeScore = 0;
		uint32_t cumulativeDissimilarityScore = 0;
		uint32_t perfectlyPlacedPieces = 0;
		uint32_t zeroMatchPieces = 0;
		uint32_t matchedBorder = 0;
	};
}

#endif //ETERNITYII_SCOREREPORT_HH
