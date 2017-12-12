#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "Timer.h"
#include "Delegate.h"

class Player;
class GameplayManager;
class EnemySpawner
{
	sf::FloatRect bounds;
	float accumulator;
	std::shared_ptr<Player> playerReference;
	GameplayManager *managerReference;
	float interval;
	unsigned difficultyLevel;
	void spawnEnemy();

	float calculateInterval() const;
	
public:
	Delegate<unsigned> OnEnemySpawn;
	bool isActive;

	EnemySpawner() {}

	EnemySpawner(const sf::IntRect &bounds, GameplayManager *gameplayManager, unsigned difficultyLevel = 0);

	void incrementDifficultyLevel();

	void findPlayer();

	void reset(float interval);

	void update(const Time::TimeData &timeData);

};

#endif