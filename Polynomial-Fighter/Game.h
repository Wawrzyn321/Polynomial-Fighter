#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
	sf::RenderWindow *window = nullptr;

	static void hideConsole();

	void performShutdown() const;
public:
	Game();

	void run();

	~Game();
};

#endif