#include "Game.h"
#include "MainMenu.h"
#include "Colors.h"
#include "Utility.h"

void Game::hideConsole()
{
#ifdef  _WIN32
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
}

void Game::performShutdown() const
{
	while (window->getSize().x > 100 && window->isOpen())
	{
		auto size = window->getSize();
		float x = float(size.x);
		window->setSize({
			unsigned(lerp(x, 0.0f, 0.001f)),
			unsigned(lerp(float(size.y), 0.0f, 0.001f))
		});
	}
}

Game::Game()
{
	Colors::load();
	//hideConsole();
}

void Game::run()
{
	window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(GameData::WINDOW_SIZE.x),
		static_cast<unsigned int>(GameData::WINDOW_SIZE.y)), "Polynomial Fighter");

	window->setFramerateLimit(120);

	MainMenu menu(window);
	menu.mainLoop();

	performShutdown();
}

Game::~Game()
{
	delete window;
}