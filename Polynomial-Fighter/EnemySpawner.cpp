#include "EnemySpawner.h"
#include "Enemy.h"
#include "PolynomialGenerator.h"
#include "Utility.h"
#include "EntityManager.h"
#include "GameplayManager.h"
#include "Player.h"

void EnemySpawner::spawnEnemy()
{
	if(!playerReference)
	{
		Debug::PrintErrorFormatted("EnemySpawner::spawnEnemy: player not set!\n");
		return;
	}

	unsigned deg = clamp(difficultyLevel+1, unsigned(0), GameData::MAX_POLYNOMINAL_DEGREE);
	unsigned valuesRange = clamp(difficultyLevel+1, unsigned(0), GameData::MAX_POLYNOMINAL_VALUE);
	float speed = 0.1f + difficultyLevel*0.03f;
	PolynomialProductForm pff = PolynomialGenerator::generatePolynomial(deg, valuesRange);
	sf::Vector2f position = getPointOnIntRect(bounds);

	auto e = std::make_shared<Enemy>(Enemy(position, playerReference->getPosition(), speed, pff));
	e->DeathEvent.add(std::bind(&GameplayManager::EnemyDestroyed, managerReference, std::placeholders::_1));
	EntityManager::instance()->addEntity(e);

	OnEnemySpawn(e->getId());
}

float EnemySpawner::calculateInterval() const
{
	// f(x) = 1000 * (4.5 + 0.1x) / (1 + 0.1x) -> (1000, 4500>
	float f = (4.5f + difficultyLevel*0.1f) / float(1 + difficultyLevel*0.1f);
	float multiplier = 1 / Time::MICRO_TO_MILI;
	return multiplier * f;
}

EnemySpawner::EnemySpawner(const sf::IntRect& bounds, GameplayManager* gameplayManager, unsigned difficultyLevel)
{
	this->bounds = sf::FloatRect(bounds);
	this->difficultyLevel = difficultyLevel;
	managerReference = gameplayManager;
	interval = calculateInterval();
	accumulator = interval*0.5f;
	isActive = true;
}

void EnemySpawner::incrementDifficultyLevel()
{
	difficultyLevel++;
	interval = calculateInterval();
	accumulator = 0;
}

void EnemySpawner::findPlayer()
{
	playerReference = EntityManager::instance()->findEntityOfType<Player>();
}

void EnemySpawner::reset(float interval)
{
	this->interval = interval;
	difficultyLevel = 0;

	accumulator = 0;
}

void EnemySpawner::update(const Time::TimeData &timeData)
{
	if (!isActive) return;

	accumulator += timeData.getScaledDeltaTimeInMili();
	if(accumulator>=interval)
	{
		accumulator -= interval;
		spawnEnemy();
	}
}