#ifndef GAME_H
#define GAME_H
#include "GameplayManager.h"

class EntityManager;
class Gameplay {
	EntityManager* em;
	GameplayManager *gameplayManager;
	sf::RenderWindow* window;

	void handleEvents() const;

	void update() const;

	void draw() const;
public:
	bool isRunning;
	Gameplay(sf::RenderWindow* window);

	void mainLoop();

	~Gameplay();
};

#endif
