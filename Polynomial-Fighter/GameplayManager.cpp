#include "GameplayManager.h"
#include "GameData.h"
#include "Debug.h"
#include "Player.h"
#include "EntityManager.h"
#include "InputFieldParser.h"
#include "Enemy.h"
#include <cassert>
#include "FleetingText.h"
#include "Colors.h"

void GameplayManager::startNextLevel()
{
	currentStage++;
	targetEnemiesNumber = (currentStage + 1) * 3;
	alreadySpawnedEnemies = 0;

	spawner.incrementDifficultyLevel();
	spawner.isActive = true;

	player->addRounds(RandomGenerator::getInt(2, 5));
	if (currentStage % 2 == 0) {
		player->addHealthCapacity(1.0f, true);
	}

	scoreManager.stageFinished();
}

#pragma region Events

void GameplayManager::EnemySpawned(unsigned id)
{
	alreadySpawnedEnemies++;
	if (alreadySpawnedEnemies == targetEnemiesNumber)
	{
		spawner.isActive = false;
	}
	enemiesAlive++;
}

void GameplayManager::EnemyDestroyed(unsigned id)
{
	cameraShake.shake(2, 70);
	enemiesAlive--;
	if (enemiesAlive == 0 && alreadySpawnedEnemies == targetEnemiesNumber)
	{
		startNextLevel();
	}
	scoreManager.onEnemyKilled(id);
}

void GameplayManager::TextSubmitted(const std::string &text) const
{
	RequestValue value = InputFieldParser::parse(text);

	std::vector<std::shared_ptr<Entity>> entities = EntityManager::instance()->findEntitiesByTag(GameData::TAG_ENEMY);

	player->processConsoleInput(value, entities);
}

void GameplayManager::PlayerDestroyed()
{
	cameraShake.shake(5, 150);
	spawner.isActive = false;

	std::vector<std::shared_ptr<Entity>> entities = EntityManager::instance()->findEntitiesByTag(GameData::TAG_ENEMY);
	for (auto &e : entities)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy>(entities.back());
		assert(enemy);
		enemy->setState(Enemy::State::STOPPED);
	}

	scoreManager.showFinalScore(allDestroyedEnemies);

	SoundManager::instance()->playSound(GameData::SOUND_GAME_FAILURE);
}

#pragma endregion

#pragma region Initializing members

void GameplayManager::initGraphics()
{
	float r = 0.2f*GameData::WINDOW_SIZE.x*0.9f;
	ring = sf::CircleShape(r, 32);
	ring.setOrigin(r, r);
	ring.setOutlineThickness(r*0.1f);
	ring.setPosition({ GameData::WINDOW_SIZE.x *0.5f, GameData::WINDOW_SIZE.y *0.5f });
	ring.setFillColor(sf::Color::Transparent);
	ring.setOutlineColor(colorWithAlpha(Colors::FIRST, 63));
}

void GameplayManager::initSpawner()
{
	spawner = EnemySpawner(GameData::DEFAULT_BOUNDS, this, currentStage);
	spawner.findPlayer();
	spawner.OnEnemySpawn.add(std::bind(&GameplayManager::EnemySpawned, this, std::placeholders::_1));
	spawner.isActive = true;
}

void GameplayManager::initPlayer() {
	player = std::make_shared<Player>(sf::Vector2f(GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.5f));
	player->DeathEvent.add(std::bind(&GameplayManager::PlayerDestroyed, this));
	EntityManager::instance()->addEntity(player, true);
}

void GameplayManager::initInputField()
{
	if (inputField != nullptr)
	{
		delete inputField;
	}

	inputField = new InputField(
	{ GameData::WINDOW_SIZE.x * 0.67f, GameData::WINDOW_SIZE.y * 0.89f },
	{ GameData::WINDOW_SIZE.x * 0.3f, GameData::WINDOW_SIZE.y * 0.08f }
	);
	inputField->OnTextSubmitted.clear();
	inputField->OnTextSubmitted.add(std::bind(&GameplayManager::TextSubmitted, this, std::placeholders::_1));
	EntityManager::instance()->findEntityOfType<Player>()->DeathEvent.add(std::bind(&InputField::disable, inputField));
	inputField->interactable = true;
}

#pragma endregion

GameplayManager::GameplayManager(sf::RenderWindow* window) : scoreManager(ScoreManager())
{
	cameraShake.connectWindow(window);

	initGraphics();

	reset();
}

void GameplayManager::reset()
{
	currentStage = 0;
	points = 0;
	enemiesAlive = 0;
	targetEnemiesNumber = (currentStage + 1) * 3;
	alreadySpawnedEnemies = 0;

	EntityManager::instance()->clear();
	Time::Timer::instance()->setTimeScale(1.0f);
	scoreManager.reset();

	initPlayer();
	initSpawner();
	initInputField();
}

void GameplayManager::feed(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
	{
		reset();
	}

	inputField->feed(event);
}

void GameplayManager::update(const Time::TimeData &timeData)
{
	assert(EntityManager::instance()->findEntitiesByTag(GameData::TAG_PLAYER, true).size() == 1);

	spawner.update(timeData);
	scoreManager.update(timeData);
	inputField->update(timeData);
	cameraShake.update(timeData);
}

void GameplayManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ring, states);
	scoreManager.draw(target, states);
	if (inputField != nullptr) {
		inputField->draw(target, states);
	}
}

GameplayManager::~GameplayManager()
{
	delete inputField;
}

