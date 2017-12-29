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
	Debug::PrintFormatted("startujemy nowego levela\n");
	currentStage++;
	targetEnemiesNumber = (currentStage + 1) * 3;
	alreadySpawnedEnemies = 0;

	spawner.incrementDifficultyLevel();
	spawner.isActive = true;

	player->addRounds(RandomGenerator::getInt(2, 5));

	scoreManager.stageFinished();
}

void GameplayManager::EnemySpawned(unsigned id)
{
	alreadySpawnedEnemies++;
	Debug::PrintFormatted("spawn enemisa %/%\n", alreadySpawnedEnemies, targetEnemiesNumber);
	if(alreadySpawnedEnemies == targetEnemiesNumber)
	{
		Debug::PrintFormatted("Skonczyliscmy fale % z % przec, czekam.\n", currentStage, alreadySpawnedEnemies);
		spawner.isActive = false;
	}
	enemiesAlive++;
}

void GameplayManager::EnemyDestroyed(unsigned id)
{
	enemiesAlive--;
	Debug::PrintFormatted("umar, zosta�o %/%, wciaz spawnujemy: %\n", enemiesAlive, targetEnemiesNumber, alreadySpawnedEnemies != targetEnemiesNumber);
	if (enemiesAlive == 0 && alreadySpawnedEnemies == targetEnemiesNumber)
	{
		startNextLevel();
	}
	scoreManager.onEnemyKilled(id);
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

	scoreManager.showFinalScore(allDestroyedEnemies);

	SoundManager::instance()->playSound(GameData::SOUND_GAME_FAILURE);
}

void GameplayManager::initSpawner()
{
	spawner = EnemySpawner(GameData::DEFAULT_BOUNDS, this, currentStage);
	spawner.findPlayer();
	spawner.OnEnemySpawn.add(std::bind(&GameplayManager::EnemySpawned, this, std::placeholders::_1));
	spawner.isActive = true;
}

void GameplayManager::initPlayer(){
	player = std::make_shared<Player>(sf::Vector2f(GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.5f));
	player->DeathEvent.add(std::bind(&GameplayManager::PlayerDestroyed, this));
	EntityManager::instance()->addEntity(player, true);
}

GameplayManager::GameplayManager() : scoreManager(ScoreManager())
{
	currentStage = 0;
	points = 0;
	enemiesAlive = 0;
	targetEnemiesNumber = (currentStage + 1) * 3;
	alreadySpawnedEnemies = 0;

	initPlayer();

	initSpawner();
}

void GameplayManager::update(const Time::TimeData &timeData)
{
	spawner.update(timeData);
	scoreManager.update(timeData);
}

void GameplayManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	scoreManager.draw(target, states);
}

