//
// Created by Guillaume on 17/06/2019.
//

#include "DefaultScoreCalculator.hh"

etm::DefaultScoreCalculator::DefaultScoreCalculator(const etm::IBoard &board) : m_board(board) {}

const etm::ScoreReport &etm::DefaultScoreCalculator::computeScore() {
	m_report = ScoreReport();
	std::vector<uint32_t> expectedColor;
	std::vector<uint32_t> actualColor;
	expectedColor.resize(m_board.getSize().width * m_board.getSize().height * 4, 0);
	actualColor.resize(m_board.getSize().width * m_board.getSize().height * 4, 0);
	Position2D currentPos;
	for (currentPos.y = 0; currentPos.y < m_board.getSize().height; ++currentPos.y) {
		for (currentPos.x = 0; currentPos.x < m_board.getSize().width; ++currentPos.x) {
			auto expectColors = getExpectedColors(currentPos);
			auto actColors = m_board.getRotatedEdges(currentPos);
			for (uint32_t i = 0; i < 4; i++) {
				expectedColor[m_board.getLinearPosition(currentPos) * 4 + i] = expectColors[i];
				actualColor[m_board.getLinearPosition(currentPos) * 4 + i] = actColors[i];
			}
		}
	}
	for (uint32_t i = 0; i < expectedColor.size(); ++i) {
		++m_report.maxScore;
		if (actualColor[i] != 0 && expectedColor[i] == actualColor[i])
			++m_report.cumulativeScore;
		//TODO: calculate other score type in the report
	}
	return m_report;
}

const etm::ScoreReport &etm::DefaultScoreCalculator::getComputedScore() const {
	return m_report;
}

//TODO: generify size
std::array<uint32_t, 4> etm::DefaultScoreCalculator::getExpectedColors(const etm::Position2D &pos) {
	std::array<uint32_t, 4> colors{};
	for (uint32_t i = 0; i < 4; ++i) {
		if ((i == 0 && pos.y == 0) || (i == 1 && pos.x == m_board.getSize().width - 1) ||
		    (i == 2 && pos.y == m_board.getSize().height - 1) || (i == 3 && pos.x == 0)) {
			colors[i] = m_board.getDefaultEdgeColor();
			continue;
		}
		static const std::array<std::pair<short, short>, 4> iToMod = {
				std::make_pair(0, -1),
				std::make_pair(1, 0),
				std::make_pair(0, 1),
				std::make_pair(-1, 0),
		};
		Position2D nextPos{pos.x + iToMod[i].first, pos.y + iToMod[i].second};
		colors[i] = m_board.getRotatedEdges(nextPos)[i];
	}
	return colors;
}
