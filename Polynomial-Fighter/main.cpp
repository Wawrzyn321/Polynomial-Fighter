#include <SFML/Window.hpp>
#include "EntityManager.h"
#include "ExampleEntities.h"
#include "ParticleSystem.h"
#include "PolynomialGeneralForm.h"
#include "PolynomialProductForm.h"
#include "PolynomialMultipler.h"
#include "PolynomialGenerator.h"

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

class TestEntity : public Entity
{
public:
	TestEntity(const std::string &name = "", const std::string &tag ="") :
			Entity(name, tag)
	{}

	sf::Vector2f getPosition() override
	{
		return sf::Vector2f();
	}

	void setPosition(sf::Vector2f position) override
	{

	}
};

int main()
{
	//#ifdef  _WIN32
	//	//hide console
	//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	//#endif

//	EntityManager *entityManager = EntityManager::instance();

	//test entity managera
//	entityManager->addEntity(make_shared<TestEntity>("n1", "t1"));
//	entityManager->addEntity(make_shared<TestEntity>("n2", "t1"));
//	entityManager->addEntity(make_shared<TestEntity>("n3", "t2"));
//	entityManager->addEntity(make_shared<TestEntity>("n4", "t2"));
//
//	auto entities = entityManager->getEntities();
//	for (auto &i : entities)
//	{
//		auto entity = i.lock();
//		cout << "Jaka jestes? Jestem " << entity->name << " z " << entity->tag << endl;
//	}
//
//	auto a = entityManager->findEntityByName("n3");
//	cout << "Jaka jestes? Jestem " << a.lock()->name << " z " << a.lock()->tag << endl;
//
//	entityManager->deleteEntity(a);
//
//	entities = entityManager->findEntitiesByTag("t2");
//	for (auto &i : entities)
//	{
//		auto entity = i.lock();
//		cout << "Jaka jestes? Jestem " << entity->name << " z " << entity->tag << endl;
//	}
	//koniec testu

	//test wielomianow
//	PolynomialGeneralForm wielomian;
//	wielomian.setCoefficient(2, -3);
//	wielomian.setCoefficient(0, -1);
//	wielomian.setCoefficient(1, 2);
//	wielomian.setCoefficient(4, 5);
//
//	cout << wielomian.getCoefficient(4) << endl;
//	cout << wielomian.getCoefficient(3) << endl;
//	cout << wielomian.getCoefficient(2) << endl;
//	cout << wielomian.getCoefficient(1) << endl;
//	cout << wielomian.getCoefficient(0) << endl;
//	cout << wielomian.toString() << endl;
//
//	PolynomialProductForm wielomian2;
//	wielomian2.addFactor(2, -1);
//	wielomian2.addFactor(-3, -2);
//	auto wynik = PolynomialMultipler::generalForm(wielomian2);
//	cout << endl << "Wynik mnozenia: " << wynik.toString() << endl;

	PolynomialProductForm wielomianLosowy = PolynomialGenerator::generatePolynomial(3, 2);
	auto wielomianLosowyOgolny = PolynomialMultipler::generalForm(wielomianLosowy);
	cout << "Jaki jestes? Losowy w postaci ogolnej: " << wielomianLosowyOgolny.toString() << endl;
	cout << "A to moje pierwiastki:" << endl;

	auto roots = wielomianLosowy.getRoots();
	for (auto &i : roots)
	{
		cout << i << endl;
	}
	//koniec testu

//	addEntities(entityManager);

//	sf::RenderWindow window(sf::VideoMode(1024, 768), "PF");
//
//	Time::Timer *timer = Time::Timer::instance();
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed) {
//				window.close();
//				break;
//			}
//
//			if (event.type == sf::Event::MouseMoved) {}
//
//			if(event.type == sf::Event::MouseWheelMoved)
//			{
//				timer->setTimeScale(timer->getTimeScale() + event.mouseWheel.delta*0.25f);
//			}
//		}
//
//		Time::TimeData deltaTime = timer->getTimeData();
//
//		entityManager->update(deltaTime);
//
//		window.clear();
//		entityManager->draw(window);
//		window.display();
//	}

//	delete entityManager;
	return 0;
}