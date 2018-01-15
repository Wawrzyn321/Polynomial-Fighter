#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include "EnemySpawner.h"
#include "ScoreManager.h"
#include "Entity.h"
#include "CameraShake.h"
#include "InputField.h"
#include "PauseController.h"
#include "FinalScreen.h"

class Gameplay;
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
	CameraShake cameraShake;
	PauseController pauseController;
	sf::CircleShape ring;
	Gameplay* gameplay = nullptr;
	InputField *inputField = nullptr;
	std::shared_ptr<Player> player;
	std::unique_ptr<FinalScreen> finalScreen{};

	void startNextLevel();
public:
	void EnemySpawned(unsigned id);
	void EnemyDestroyed(unsigned id);
	void TextSubmitted(const std::string &text) const;
	void PlayerDestroyed();

	void initGraphics();
	void initSpawner();
	void initPlayer();
	void initInputField();

	GameplayManager(){}
	GameplayManager(Gameplay* gameplay, sf::RenderWindow* window);
	GameplayManager(const GameplayManager &) {}

	void bindExitAction(Gameplay* game);

	void reset();

	void feed(const sf::Event& event);

	void update(const Time::TimeData &timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	~GameplayManager();
};


#endif