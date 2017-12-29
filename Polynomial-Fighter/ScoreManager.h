#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H
#include "ScoreManagerGUI.h"
#include <memory>
#include "Timer.h"

class ScoreManager
{
	unsigned enemiesKilledCount;
	unsigned points;
	unsigned stageNo;

	std::unique_ptr<ScoreManagerGUI> gui;
public:
	ScoreManager();
	ScoreManager(const ScoreManager &) {}
	ScoreManager &operator=(ScoreManager& sm) { return sm; }

	void onEnemyKilled(unsigned id);

	void stageFinished();

	void showFinalScore(unsigned destroyedEnemies) const;

	void update(const Time::TimeData& timeData) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	const unsigned int pointsEnemyDestroyed = 50;
	const unsigned int pointsStageFinished = 500;
};

#endif