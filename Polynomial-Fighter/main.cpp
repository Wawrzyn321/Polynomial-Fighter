#include <SFML/Window.hpp>
#include "EntityManager.h"
#include "ExampleEntities.h"
#include "ParticleSystem.h"

using namespace std;

void addEntities(EntityManager *entityManager){
	entityManager->addEntity(make_shared<EllipseWalker>(EllipseWalker({ 200, 300 }, { 100, 200 }, 2)));

	entityManager->addEntity(make_shared<ColorChanger>(ColorChanger({ 700, 400 }, 1)));

	weak_ptr<Entity> e = entityManager->findEntityByName("Ellipse Walker");
	entityManager->addEntity(make_shared<TransformObserver>(TransformObserver({ 900, 700 }, e)));

	//todo join constructor & building?
	ParticleSystem ps = ParticleSystem();
	ps.startBuilding({ 20, 750 })
		->setAmount(20)
		->setDrag(2.0f)
		->setColor(sf::Color::Blue)
		->setDispersion({ 1, -0.7f }, 40)
		->setSize(10, 0.4f)
		->setStartVelocity(1.7f, 0.4f)
		->setTime(3)
		->setRepeating(true)
		->finishBuilding();
	entityManager->addEntity(make_shared<ParticleSystem>(ps));

	entityManager->addEntity(make_shared<EmergencyBlinker>(EmergencyBlinker({ 500, 50 }, 1e3)));

	entityManager->addEntity(make_shared<TransformWanderer>(TransformWanderer({ 300,300 }, e)));
	entityManager->addEntity(make_shared<TransformWanderer>(TransformWanderer({ 400,400 }, e)));
	entityManager->addEntity(make_shared<TransformWanderer>(TransformWanderer({ 500,500 }, e)));
}

int main()
{
	//#ifdef  _WIN32
	//	//hide console
	//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	//#endif

	EntityManager *entityManager = EntityManager::instance();
	addEntities(entityManager);

	sf::RenderWindow window(sf::VideoMode(1024, 768), "PF");

	Time::Timer *timer = Time::Timer::instance();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}

			if (event.type == sf::Event::MouseMoved) {}

			if(event.type == sf::Event::MouseWheelMoved)
			{
				timer->setTimeScale(timer->getTimeScale() + event.mouseWheel.delta*0.25f);
			}
		}

		Time::TimeData deltaTime = timer->getTimeData();

		entityManager->update(deltaTime);

		window.clear();
		entityManager->draw(window);
		window.display();
	}
	delete entityManager;
	return 0;
}