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

	unsigned deg = clamp(difficultyLevel + 1, unsigned(0), GameData::MAX_POLYNOMINAL_DEGREE);
	unsigned valuesRange = clamp((difficultyLevel + 1) * 2, unsigned(0), GameData::MAX_POLYNOMINAL_VALUE);
	float speed = difficultyLevel + 0.2f;
	PolynomialProductForm pff = PolynomialGenerator::generatePolynomial(deg, valuesRange);
	sf::Vector2f position = getPointOnIntRect(bounds);

	auto e = std::make_shared<Enemy>(Enemy(position, playerReference->getPosition(), speed, pff));
	e->DeathEvent.add(std::bind(&GameplayManager::EnemyDestroyed, managerReference, std::placeholders::_1));
	EntityManager::instance()->addEntity(e);

	OnEnemySpawn(e->getId());
}

float EnemySpawner::calculateInterval() const
{
	// f(x) = 1000 * (2.5 + x) / (1 + x) -> (1000, 2500>
	return 1000.0f * (2.5f + difficultyLevel) / float(1 + difficultyLevel);
}

EnemySpawner::EnemySpawner(const sf::IntRect& bounds, GameplayManager* gameplayManager, unsigned difficultyLevel)
{
	this->bounds = sf::FloatRect(bounds);
	this->difficultyLevel = difficultyLevel;
	managerReference = gameplayManager;
	interval = calculateInterval();
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
	accumulator += timeData.getScaledDeltaTimeInMili();
	if(accumulator>=interval)
	{
		accumulator -= interval;
		spawnEnemy();
	}
}
