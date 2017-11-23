#include "RandomGenerator.h"
#include "Timer.h"
#include "EntityManager.h"
#include "Bullet.h"
#include "Player.h"

using namespace std;

void addBullet(){
	auto b = std::make_shared<Bullet>(Bullet("ball", { 100,100 }, 5));
	b->setTarget(EntityManager::instance()->findEntityByName(GameData::NAME_PLAYER).lock()->getPosition(), GameData::NAME_PLAYER, 2, 2);
	EntityManager::instance()->addEntity(b);
}

int main()
{
//#ifdef  _WIN32
//	//hide console
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

	auto em = EntityManager::instance();
	auto t = Time::Timer::instance();



	Player p = Player({ GameData::WINDOW_SIZE.x*0.5f, GameData::WINDOW_SIZE.y*0.5f });
	em->addEntity(std::shared_ptr<Entity>(static_cast<Entity*>(&p)));
	//em->addEntity(std::make_shared<Player>(p));

	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_SIZE.x, GameData::WINDOW_SIZE.y), "pf");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
				addBullet();
			}
		}

		auto deltaTime = t->getTimeData();
		em->update(deltaTime);
		em->removeMarked();

		window.clear();
		em->draw(window);
		window.display();
	}

	system("pause");
	return 0;
}
