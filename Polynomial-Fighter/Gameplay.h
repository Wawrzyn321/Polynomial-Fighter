#ifndef GAME_H
#define GAME_H
#include "GameplayManager.h"

class EntityManager;
class Gameplay {
	EntityManager* em;
	GameplayManager *gameplayManager;
	sf::RenderWindow* window;
	bool isRunning;

	void handleEvents();

	void update() const;

	void draw() const;
public:
	Gameplay(sf::RenderWindow* window);

	void mainLoop();

	~Gameplay();
};

#endif
