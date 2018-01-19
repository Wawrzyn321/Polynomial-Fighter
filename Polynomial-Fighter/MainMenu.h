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

	void handleMenuEvents(const sf::Event::KeyEvent& keyEvent);

	void handleSplashEvents(const sf::Event::KeyEvent& keyEvent);

	void handleHighScoreKeys(const sf::Event::KeyEvent& keyEvent);

	void handleHowToKeys(const sf::Event::KeyEvent& keyEvent);

	void handleAuthorsKeys(const sf::Event::KeyEvent& keyEvent);

	void handleRingRotation(const sf::Event &event) const;

	void handleRollingListsReleasedEvents(const sf::Event::KeyEvent& key) const;

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
