#include <SFML/Window.hpp>
#include "EntityManager.h"
#include "ExampleEntities.h"
#include "APSBuilder.h"
#include "AdvancedParticleSystemData.h"
#include "AdvancedParticleSystem.h"

using namespace std;

void addEntities(EntityManager *entityManager){
	entityManager->addEntity(make_shared<EllipseWalker>(EllipseWalker({ 200, 300 }, { 100, 200 }, 2)));

	entityManager->addEntity(make_shared<ColorChanger>(ColorChanger({ 700, 400 }, 1)));

	weak_ptr<Entity> e = entityManager->findEntityByName("Ellipse Walker");
	entityManager->addEntity(make_shared<TransformObserver>(TransformObserver({ 900, 700 }, e)));

	entityManager->addEntity(make_shared<EmergencyBlinker>(EmergencyBlinker({ 500, 50 }, 1e3)));

	entityManager->addEntity(make_shared<TransformWanderer>(TransformWanderer({ 300,300 }, e)));
	entityManager->addEntity(make_shared<TransformWanderer>(TransformWanderer({ 400,400 }, e)));
	entityManager->addEntity(make_shared<TransformWanderer>(TransformWanderer({ 500, 500 }, e)));


	auto aps = APSBuilder::startBuilding({ 512, 300 })
		->setMainData(5000, 100, WORLD)
		->setLooping(true)
		->setIntervals(2000, 2000, 0)
		->setAsCircle(10, 32)
		->setColors(RandomGenerator::getRandomColor(), 0.9f, sf::Color::Transparent, 0.1f, 0.001f)
		->setRandomColor(true)
		->setVelocity(0.4f, 0.5f, 0.996f)
		->setScaling(0.999f)
		->setGravity(true, sf::Vector2f(0, 1)*0.25f)
		->finishBuilding(true);
	aps->name = "PARTICLES";
	entityManager->addEntity(make_shared<AdvancedParticleSystem>(*aps));


	auto aps2 = APSBuilder::startBuilding({ 900, 100 })
		->setMainData(0, 100)
		->setLooping(true)
		->setIntervals(1000, 0, 0)
		->setDispersion(10, sf::Vector2f(0, 1))
		->setAsCircle(5, 12)
		->setColors(sf::Color::Red, 0.2f, sf::Color::Transparent, 0.0f, 0.001f)
		->setVelocity(1.1f, 0.5f, 0.996f)
		->setScaling(0.999f)
		->finishBuilding(true);
	entityManager->addEntity(make_shared<AdvancedParticleSystem>(*aps2));
}

void APS_demo(){
	EntityManager *entityManager = EntityManager::instance();
	addEntities(entityManager);

	sf::RenderWindow window(sf::VideoMode(1024, 768), "PF");

	Time::Timer *timer = Time::Timer::instance();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)) {
				window.close();
				break;
			}

			if (event.type == sf::Event::MouseMoved)
			{
				shared_ptr<Entity> e = entityManager->findEntityByName("PARTICLES").lock();
				shared_ptr<AdvancedParticleSystem> derived = dynamic_pointer_cast<AdvancedParticleSystem> (e);
				derived->setPosition({ (float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y });
			}

			if (event.type == sf::Event::MouseWheelMoved)
			{
				timer->setTimeScale(timer->getTimeScale() + event.mouseWheel.delta*0.25f);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::R)
			{
				shared_ptr<Entity> e = entityManager->findEntityByName("PARTICLES").lock();
				shared_ptr<AdvancedParticleSystem> derived = dynamic_pointer_cast<AdvancedParticleSystem> (e);
				derived->revive();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::S)
			{
				shared_ptr<Entity> e = entityManager->findEntityByName("PARTICLES").lock();
				shared_ptr<AdvancedParticleSystem> derived = dynamic_pointer_cast<AdvancedParticleSystem> (e);
				derived->space = derived->space == SELF ? WORLD : SELF;
			}
		}

		Time::TimeData deltaTime = timer->getTimeData();

		entityManager->update(deltaTime);

		window.clear();
		entityManager->draw(window);
		window.display();
	}
	delete entityManager;
}

int main()
{
	//#ifdef  _WIN32
	//	//hide console
	//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	//#endif
	APS_demo();
	return 0;
}
