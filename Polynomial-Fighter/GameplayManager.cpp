#include "GameplayManager.h"
#include "GameData.h"
#include "Debug.h"
#include "Player.h"
#include "EntityManager.h"
#include "InputFieldParser.h"
#include "Enemy.h"
#include <cassert>

void GameplayManager::EnemySpawned(unsigned id)
{
	alreadySpawneEnemies++;
	if(alreadySpawneEnemies == targetEnemiesNumber)
	{
		spawner.isActive = false;
	}
}

void GameplayManager::EnemyDestroyed(unsigned id)
{
	alreadySpawneEnemies--;
	points += 100;
	if(alreadySpawneEnemies == 0)
	{
		points += 1000;
		difficultyLevel++;
		spawner.incrementDifficultyLevel();
		spawner.isActive = true;
	}
}

void GameplayManager::TextSubmitted(std::string text)
{
	InputFieldParser p = InputFieldParser();
	auto values = p.parse(text);

	auto entities = EntityManager::instance()->findEntitiesByTag(GameData::TAG_ENEMY);

	std::vector<DesignatedTarget> targets;
	for(auto e : entities)
	{
		for(auto v : values)
		{
			std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(e);
			assert(enemy);
			if(enemy->canBeDamagedBy(v))
			{
				targets.push_back({enemy->getId(), v});
			}
		}
	}
	player->appendTargets(targets);
}

void GameplayManager::PlayerDestroyed(int i)
{
	spawner.isActive = false;
	Debug::PrintFormatted("UMARLEM, ale za to mam % punktow\n", points);
}

GameplayManager::GameplayManager()
{
	difficultyLevel = 0;
	points = 0;
	targetEnemiesNumber = (difficultyLevel + 1) * 3;
	alreadySpawneEnemies = 0;

	player = new Player({ GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.5f });
	player->DeathEvent.add(std::bind(&GameplayManager::PlayerDestroyed, this, std::placeholders::_1));
	EntityManager::instance()->addEntity(std::shared_ptr<Entity>(player));

	spawner = EnemySpawner(GameData::DEFAULT_BOUNDS, this, difficultyLevel);
	spawner.findPlayer();
	spawner.OnEnemySpawn.add(std::bind(&GameplayManager::EnemySpawned, this, std::placeholders::_1));
}

void GameplayManager::update(const Time::TimeData &timeData)
{
	spawner.update(timeData);
}