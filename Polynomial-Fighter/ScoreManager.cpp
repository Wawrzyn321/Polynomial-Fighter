#include "ScoreManager.h"
#include "Timer.h"
#include <cassert>
#include "HighscoresService.h"
#include "Enemy.h"
#include "EntityManager.h"

ScoreManager::ScoreManager()
{
	enemiesKilledCount = 0;
	points = 0;

	gui = std::make_unique<ScoreManagerGUI>(
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.67f, GameData::WINDOW_SIZE.y*0.03f),
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f));
	gui->stageFinished(1);
}

void ScoreManager::onEnemyKilled(unsigned id)
{
	auto e = EntityManager::instance()->findEntityById(id);
	auto enemy = std::dynamic_pointer_cast<Enemy>(e);
	assert(enemy);

	points += pointsEnemyDestroyed*enemy->getPolynomial()->getOriginalDegree();
	enemiesKilledCount++;
	gui->setTargetPoints(points);
}

void ScoreManager::stageFinished()
{
	points += pointsStageFinished;
	stageNo++;
	gui->setTargetPoints(pointsStageFinished, true);
	gui->stageFinished(stageNo);
}

unsigned ScoreManager::getPoints() const
{
	return points;
}

void ScoreManager::showFinalScore() const
{
	HighscoreService::addScore(points);

	gui->updateScoreToFinal();
}

void ScoreManager::reset()
{
	enemiesKilledCount = 0;
	points = 0;
	gui->reset();
}

void ScoreManager::update(const Time::TimeData &timeData) const
{
	gui->update(timeData);
}

void ScoreManager::earlyDraw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	gui->earlyDraw(target, states);
}

void ScoreManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*gui, states);
}
