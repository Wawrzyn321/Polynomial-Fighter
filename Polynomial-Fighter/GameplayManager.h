#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "EnemySpawner.h"
#include "Entity.h"

class GameplayManager
{
	unsigned difficultyLevel;
	unsigned points;
	unsigned targetEnemiesNumber;
	unsigned alreadySpawnedEnemies;

	EnemySpawner spawner;
	std::shared_ptr<Player> player;
	void startNextLevel();
public:
	void EnemySpawned(unsigned id);
	void EnemyDestroyed(unsigned id);
	void TextSubmitted(const std::string &text) const;
	void PlayerDestroyed(int i);

	GameplayManager();

	void GameplayManager::update(const Time::TimeData &timeData);
};


#endif