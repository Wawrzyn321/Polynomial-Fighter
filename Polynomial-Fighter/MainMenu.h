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
		AUHTORS,
	};

private:
	sf::RenderWindow* window;
	GUIAnimator *animator;
	StopWatch *stopWatch;
	bool isRunning;

	void handleMenuEvents(sf::Keyboard::Key key);

	void handleHighScoreKeys(sf::Keyboard::Key key);

	void handleHowToKeys(sf::Keyboard::Key key);

	void handleAuthorsKeys(sf::Keyboard::Key key);

	void handleRingRotation(const sf::Event &event) const;

	void handleEvents();

	void update() const;

	void exitGame();

	void onGame();

public:
	State state;

	MainMenu(sf::RenderWindow* window);

	void mainLoop();

	void draw() const;

	~MainMenu();
};


#endif
