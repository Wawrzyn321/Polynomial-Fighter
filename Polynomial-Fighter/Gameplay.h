#ifndef GAME_H
#define GAME_H
#include "GameplayManager.h"

class EntityManager;
class Gameplay {
public:
	enum class State
	{
		ON,
		SHOWING_HIGHSCORE,
		PROMPTING_NEXT,
		EXITING,
	};
private:
	EntityManager* em;
	GameplayManager *gameplayManager;
	sf::RenderWindow* window;

	void handleEvents() const;

	void update() const;

	void draw() const;
public:
	State state;
	bool isRunning;

	Gameplay(sf::RenderWindow* window);

	void mainLoop();

	~Gameplay();
};

#endif
