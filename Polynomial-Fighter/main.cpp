#include "Gameplay.h"

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



	while (true) {
		GamePlay g(&window);
		g.mainLoop();
	}
	
	return 0;
}
