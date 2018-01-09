#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Gameplay.h"
#include "GUIAnimator.h"

class MainMenu
{
	sf::RenderWindow* window;
	GUIAnimator *animator;
	tgui::Gui tGUI;
	bool isRunning;

	void handleEvents();

	void update();

	void draw();
public:
	MainMenu(sf::RenderWindow* window);

	void mainLoop();

	~MainMenu();
};


#endif
