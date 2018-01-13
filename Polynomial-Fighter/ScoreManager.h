#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H
#include "ScoreManagerGUI.h"
#include <memory>
#include "Timer.h"
#include "FinalScreen.h"

class FinalScreen;
class ScoreManager
{
	unsigned enemiesKilledCount{};
	unsigned points{};
	unsigned stageNo{};

	std::unique_ptr<ScoreManagerGUI> gui{};
	std::unique_ptr<FinalScreen> finalScreen{};
public:
	ScoreManager();
	ScoreManager(const ScoreManager &) {}
	ScoreManager &operator=(const ScoreManager& sm) { return *this; }

	void onEnemyKilled(unsigned id);

	void stageFinished();

	void showFinalScore(unsigned destroyedEnemies);

	void reset();

	void update(const Time::TimeData& timeData) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	const unsigned int pointsEnemyDestroyed = 50;
	const unsigned int pointsStageFinished = 500;
};

#endif