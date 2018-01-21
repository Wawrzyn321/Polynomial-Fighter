#include "GameplayManager.h"
#include "GameData.h"
#include "Player.h"
#include "SoundManager.h"
#include "EntityManager.h"
#include "InputFieldParser.h"
#include "Enemy.h"
#include <cassert>
#include "Gameplay.h"
#include "Colors.h"
#include "RandomGenerator.h"
#include "AssetManager.h"

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
	const float healAmount = 0.2f;

	if (player->getAlive()) {
		auto e = EntityManager::instance()->findEntityById(id);
		assert(e);
		auto enemy = std::dynamic_pointer_cast<Enemy>(e);
		assert(enemy);
		player->heal(enemy->getPolynomial()->getOriginalDegree()*healAmount);
	}

	cameraShake.shake(3, 80);
	enemiesAlive--;
	allDestroyedEnemies++;
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
	cameraShake.shake(8, 200);
	spawner.isActive = false;

	std::vector<std::shared_ptr<Entity>> entities = EntityManager::instance()->findEntitiesByTag(GameData::TAG_ENEMY);
	for (auto &e : entities)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy>(entities.back());
		assert(enemy);
		enemy->setState(Enemy::State::STOPPED);
	}

	gameplay->state = Gameplay::State::SHOWING_HIGHSCORE;

	pauseController.forceSwitchTo(false);
	scoreManager.showFinalScore();
	finalScreen = std::make_unique<FinalScreen>(scoreManager.getPoints(), allDestroyedEnemies, currentStage);

	SoundManager::instance()->playSound(Assets::SOUND_FAILED);

	inputLock = StopWatch(endGameDelay, true);
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
	player = std::make_shared<Player>(GameData::WINDOW_CENTER);
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
	{ GameData::WINDOW_SIZE.x * 0.3f, GameData::WINDOW_SIZE.y * 0.08f },
	&pauseController);
	inputField->OnTextSubmitted.clear();
	inputField->OnTextSubmitted.add(std::bind(&GameplayManager::TextSubmitted, this, std::placeholders::_1));
	EntityManager::instance()->findEntityOfType<Player>()->DeathEvent.add(std::bind(&InputField::disable, inputField));
	inputField->interactable = true;
}

#pragma endregion

GameplayManager::GameplayManager(Gameplay* gameplay, sf::RenderWindow* window) : scoreManager(ScoreManager())
{
	this->gameplay = gameplay;

	cameraShake.connectWindow(window);
	initGraphics();
	reset();
}

void GameplayManager::bindExitAction(Gameplay *game)
{
	pauseController.OnExitRequested.add(std::bind([](Gameplay *gameplay)
	{
		gameplay->isRunning = false;
	}, gameplay));
}

void GameplayManager::reset()
{
	currentStage = 0;
	enemiesAlive = 0;
	targetEnemiesNumber = (currentStage + 1) * 3;
	alreadySpawnedEnemies = 0;
	allDestroyedEnemies = 0;

	EntityManager::instance()->clear();
	Time::Timer::instance()->setTimeScale(1.0f);
	scoreManager.reset();
	finalScreen.reset();

	initPlayer();
	initSpawner();
	initInputField();
}

void GameplayManager::feed(const sf::Event& event)
{
	if (gameplay->state == Gameplay::State::ON) {
		inputField->feed(event);
		pauseController.feed(event);
	}
	if (inputLock.isRunning == false) {
		if (gameplay->state == Gameplay::State::SHOWING_HIGHSCORE)
		{
			if (event.type == sf::Event::KeyPressed && !isAuxiliaryKey(event.key))
			{
				gameplay->state = Gameplay::State::PROMPTING_NEXT;
				finalScreen->state = FinalScreen::State::PROMPT;
			}
		}
		else if (gameplay->state == Gameplay::State::PROMPTING_NEXT)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					gameplay->isRunning = false;
					gameplay->state = Gameplay::State::EXITING;
					break;
				case sf::Keyboard::Space:
				case sf::Keyboard::Return:
					reset();
					gameplay->state = Gameplay::State::ON;
				}
			}
		}
	}
}

void GameplayManager::update(const Time::TimeData &timeData)
{
	spawner.update(timeData);
	scoreManager.update(timeData);
	inputField->update(timeData);
	cameraShake.update(timeData);
	pauseController.update(timeData);
	if (finalScreen) {
		finalScreen->update(timeData);
	}
	inputLock.update(timeData);
}

void GameplayManager::earlyDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	scoreManager.earlyDraw(target, states);
}

void GameplayManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ring, states);
	scoreManager.draw(target, states);
	pauseController.draw(target, states);
	if (inputField != nullptr) {
		inputField->draw(target, states);
	}
	if (finalScreen) {
		target.draw(*finalScreen, states);
	}
}

GameplayManager::~GameplayManager()
{
	delete inputField;
	finalScreen.reset();
}
