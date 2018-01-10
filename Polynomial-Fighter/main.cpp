#include "MainMenu.h"

using namespace std;

void hideConsole()
{
	//#ifdef  _WIN32
	//	//hide console
	//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	//#endif
}

int main()
{
	hideConsole();
	
	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(GameData::WINDOW_SIZE.x),
                                          static_cast<unsigned int>(GameData::WINDOW_SIZE.y)), "pf");
    window.setFramerateLimit(120);
	SoundManager::instance()->isOn = false;

	MainMenu m(&window);
	m.mainLoop();

	while(window.getSize().x > 100)
	{
		int x = int(window.getSize().x);
		window.setSize({
			unsigned(lerp(x, 0, 0.001f)),
			unsigned(lerp(int(window.getSize().y), 0, 0.001f))
		});
	}

	/*while (true) {
		Gameplay g(&window);
		g.mainLoop();
	}*/
	
	return 0;
}
