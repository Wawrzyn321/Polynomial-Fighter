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
	auto values = InputFieldParser::parse(text);

	std::vector<std::shared_ptr<Entity>> entities = EntityManager::instance()->findEntitiesByTag(GameData::TAG_ENEMY);

	player->appendTargets(values, entities);
}

void GameplayManager::PlayerDestroyed()
{
	spawner.isActive = false;

	std::vector<std::shared_ptr<Entity>> entities = EntityManager::instance()->findEntitiesByTag(GameData::TAG_ENEMY);
	for(auto &e : entities)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy>(entities.back());
		assert(enemy);
		enemy->setState(Enemy::State::STOPPED);
	}
}

void GameplayManager::initSpawner()
{
	spawner = EnemySpawner(GameData::DEFAULT_BOUNDS, this, difficultyLevel);
	spawner.findPlayer();
	spawner.OnEnemySpawn.add(std::bind(&GameplayManager::EnemySpawned, this, std::placeholders::_1));
	spawner.isActive = true;
}

void GameplayManager::initPlayer(){
	player = std::make_shared<Player>(sf::Vector2f(GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.5f));
	player->DeathEvent.add(std::bind(&GameplayManager::PlayerDestroyed, this));
	EntityManager::instance()->addEntity(player, true);
}

GameplayManager::GameplayManager()
{
	difficultyLevel = 0;
	points = 0;
	targetEnemiesNumber = (difficultyLevel + 1) * 3;
	alreadySpawnedEnemies = 0;

	initPlayer();

	initSpawner();
}

void GameplayManager::update(const Time::TimeData &timeData)
{
	spawner.update(timeData);
}