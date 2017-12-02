#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "EnemySpawner.h"
#include "Entity.h"

class GameplayManager
{
	unsigned difficultyLevel;
	unsigned points;
	unsigned targetEnemiesNumber;
	unsigned alreadySpawneEnemies;

	EnemySpawner spawner;
	Player *player;
public:
	void EnemySpawned(unsigned id);
	void EnemyDestroyed(unsigned id);
	void TextSubmitted(std::string text);
	void PlayerDestroyed(int i);

	GameplayManager();

	void GameplayManager::update(const Time::TimeData &timeData);
};


#endif