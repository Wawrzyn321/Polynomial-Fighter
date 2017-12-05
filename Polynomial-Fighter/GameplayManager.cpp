#include "GameplayManager.h"
#include "GameData.h"
#include "Debug.h"
#include "Player.h"
#include "EntityManager.h"
#include "InputFieldParser.h"
#include "Enemy.h"
#include <cassert>

//todo funkcje zapewniajace dane liczbowe?
// osobiscie uwazam, ze najlepszym momentem dla programisty jest usuwanie przeklenstw
// z kodu po tym, jak juz skonczy debugowanie i wszystko dziala.

void GameplayManager::startNextLevel()
{
	points += 1000;
	difficultyLevel++;
	targetEnemiesNumber = (difficultyLevel + 1) * 3;
	alreadySpawnedEnemies = 0;

	spawner.incrementDifficultyLevel();
	spawner.isActive = true;
}

void GameplayManager::EnemySpawned(unsigned id)
{
	alreadySpawnedEnemies++;
	if(alreadySpawnedEnemies == targetEnemiesNumber)
	{
		Debug::PrintFormatted("Skonczyliscmy fale % z % przec, czekam.\n", difficultyLevel, alreadySpawnedEnemies);
		spawner.isActive = false;
	}
}

void GameplayManager::EnemyDestroyed(unsigned id)
{
	alreadySpawnedEnemies--;
	points += 100;
	if(alreadySpawnedEnemies == 0)
	{
		startNextLevel();
	}
}

void GameplayManager::TextSubmitted(const std::string &text) const
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
}

GameplayManager::GameplayManager()
{
	difficultyLevel = 0;
	points = 0;
	targetEnemiesNumber = (difficultyLevel + 1) * 3;
	alreadySpawnedEnemies = 0;

	player = std::make_shared<Player>(sf::Vector2f(GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.5f));
	player->DeathEvent.add(std::bind(&GameplayManager::PlayerDestroyed, this, std::placeholders::_1));
	EntityManager::instance()->addEntity(player, true);

	spawner = EnemySpawner(GameData::DEFAULT_BOUNDS, this, difficultyLevel);
	spawner.findPlayer();
	spawner.OnEnemySpawn.add(std::bind(&GameplayManager::EnemySpawned, this, std::placeholders::_1));
	spawner.isActive = true;
}

void GameplayManager::update(const Time::TimeData &timeData)
{
	spawner.update(timeData);
}