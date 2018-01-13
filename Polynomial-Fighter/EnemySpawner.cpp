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

    auto deg = clamp(difficultyLevel + 1, unsigned(1), GameData::MAX_POLYNOMINAL_DEGREE);
	auto valuesRange = clamp(difficultyLevel + 1, unsigned(1), GameData::MAX_POLYNOMINAL_VALUE);
	PolynomialProductForm pff = PolynomialGenerator::generatePolynomial(deg, valuesRange);
	sf::Vector2f position = getPointOnIntRect(bounds, 12, 25);

	float speed = 0.1f + difficultyLevel*0.01f;
	auto e = std::make_shared<Enemy>(Enemy());
	e->init(position, playerReference->getPosition(), speed, pff);
	e->DeathEvent.add(std::bind(&GameplayManager::EnemyDestroyed, managerReference, std::placeholders::_1));
	EntityManager::instance()->addEntity(e);

	OnEnemySpawn(e->getId());
}

float EnemySpawner::calculateInterval() const
{
	// f(x) = 1000 * (4.5 + 0.1x) / (1 + 0.1x) -> (1000, 4500>
	float f = (4.5f + difficultyLevel*0.1f) / (1 + difficultyLevel * 0.1f);
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

	OnEnemySpawn.clear();
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
	if (accumulator >= interval)
	{
		accumulator -= interval;
		spawnEnemy();
	}
}