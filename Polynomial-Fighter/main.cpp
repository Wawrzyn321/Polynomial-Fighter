#include "MainMenu.h"
#include "Utility.h"

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
	Colors::load();
	hideConsole();
	
	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(GameData::WINDOW_SIZE.x),
                                          static_cast<unsigned int>(GameData::WINDOW_SIZE.y)), "Polynomial Fighter");
    window.setFramerateLimit(120);

	MainMenu m(&window);
	m.mainLoop();

	while(window.getSize().x > 100 && window.isOpen())
	{
		auto size = window.getSize();
		float x = float(size.x);
		window.setSize({
			unsigned(lerp(x, 0.0f, 0.001f)),
			unsigned(lerp(float(size.y), 0.0f, 0.001f))
		});
	}

	/*while (true) {
		Gameplay g(&window);
		g.mainLoop();
	}*/
	
	return 0;
}
