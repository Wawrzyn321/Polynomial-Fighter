#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <SFML/Graphics.hpp>
#include "Gameplay.h"
#include "GUIAnimator.h"
#include "StopWatch.h"

class MainMenu
{
public:
	enum class State
	{
		SPLASH,
		MENU,
		TO_GAME,
		EXITING,
		HIGHSCORES,
		HOW_TO,
	};

private:
	sf::RenderWindow* window;
	GUIAnimator *animator;
	StopWatch *stopWatch;
	bool isRunning;

	void handleEvents();

	void update() const;

	void finish();

public:
	State state;

	MainMenu(sf::RenderWindow* window);

	void mainLoop();

	void draw() const;

	~MainMenu();
};


#endif
