#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H
#include "ScoreManagerGUI.h"
#include <memory>
#include "Timer.h"

class FinalScreen;
class ScoreManager
{
	unsigned enemiesKilledCount{};
	unsigned points{};
	unsigned stageNo{};

	std::unique_ptr<ScoreManagerGUI> gui{};
public:
	ScoreManager();
	ScoreManager(const ScoreManager &) {}

	void onEnemyKilled(unsigned id);

	void stageFinished();

	unsigned getPoints() const;

	void showFinalScore() const;

	void reset();

	void update(const Time::TimeData& timeData) const;

	void earlyDraw(sf::RenderTarget& target, const sf::RenderStates& states) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	const unsigned int pointsEnemyDestroyed = 50;
	const unsigned int pointsStageFinished = 200;
};

#endif