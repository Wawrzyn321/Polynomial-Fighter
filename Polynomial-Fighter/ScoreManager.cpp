#include "ScoreManager.h"
#include "Timer.h"
#include "GameData.h"
#include <cassert>
#include "EntityManager.h"
#include "Enemy.h"

ScoreManager::ScoreManager()
{
	enemiesKilledCount = 0;
	points = 0;

	gui = std::make_unique<ScoreManagerGUI>(
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.67f, GameData::WINDOW_SIZE.y*0.03f),
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f));
	gui->updateStageNo(1);
}

void ScoreManager::onEnemyKilled(unsigned id)
{
	auto e = EntityManager::instance()->findEntityById(id);
	auto enemy = std::dynamic_pointer_cast<Enemy>(e);
	assert(enemy);

	points += pointsEnemyDestroyed*enemy->getOriginalDegree();
	enemiesKilledCount++;
	gui->setTargetPoints(points);
}

void ScoreManager::stageFinished()
{
	Debug::PrintFormatted("finnish");
	points += pointsStageFinished;
	stageNo++;
	gui->updateStageNo(stageNo, pointsStageFinished);
}


void ScoreManager::showFinalScore(unsigned destroyedEnemies) const
{
	gui->showFinalScore();
}

void ScoreManager::update(const Time::TimeData &timeData) const
{
	gui->update(timeData);
}

void ScoreManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*gui, states);
}