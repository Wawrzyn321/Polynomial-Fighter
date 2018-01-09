#ifndef GAME_H
#define GAME_H
#include "GameplayManager.h"

class EntityManager;
class GamePlay {
	EntityManager* em;
	GameplayManager *gameplayManager;
	sf::RenderWindow* window;
	bool isRunning;

	void handleEvents();

	void update() const;

	void draw() const;
public:
	GamePlay(sf::RenderWindow* window);

	void mainLoop();

	~GamePlay();
};

#endif
