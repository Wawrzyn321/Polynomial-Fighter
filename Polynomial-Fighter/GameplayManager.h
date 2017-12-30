#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "EnemySpawner.h"
#include "ScoreManager.h"
#include "Entity.h"
#include "InputField.h"
#include "CameraShake.h"

class GameplayManager
{
	unsigned currentStage{};
	unsigned points{};

	unsigned targetEnemiesNumber{};
	unsigned alreadySpawnedEnemies{};
	unsigned allDestroyedEnemies{};
	unsigned enemiesAlive{};

	EnemySpawner spawner;
	ScoreManager scoreManager;
	InputField inputField;
	CameraShake cameraShake;
	std::shared_ptr<Player> player;

	void startNextLevel();
public:
	void EnemySpawned(unsigned id);
	void EnemyDestroyed(unsigned id);
	void TextSubmitted(const std::string &text) const;
	void PlayerDestroyed();

	void initSpawner();
	void initPlayer();
	void initInputField();

	GameplayManager(sf::RenderWindow* window);
	GameplayManager(const GameplayManager &) {}

	void feed(const sf::Event& event);

	void update(const Time::TimeData &timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};


#endif