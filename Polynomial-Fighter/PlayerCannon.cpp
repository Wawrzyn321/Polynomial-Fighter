#include "PlayerCannon.h"
#include "Bullet.h"
#include "GameData.h"
#include "APSBuilder.h"
#include "EntityManager.h"

PlayerCannon::PlayerCannon(sf::Vector2f origin)
{
	this->origin = origin;

	numberOfRounds = GameData::DEFAULT_NUMBER_OF_ROUNDS;
}

void PlayerCannon::setTargets(const std::vector<int>& targets)
{
	this->targets.insert(this->targets.end(), targets.begin(), targets.end());
}

void PlayerCannon::shoot(float angle)
{
	/*AdvancedParticleSystem *aps = APSBuilder::startBuilding(origin)
		->setMainData(1000, 30)
		->setScaling(1.0f)
		->setVelocity(1.0f, 0.3f, 0.99f)
		->setIntervals(0, 0, 0)
		->setAsCircle(15, 16)
		->setDispersion(30, -angle)
		->setColors(sf::Color(193, 193, 193), 0.2f, sf::Color::Transparent, 0, 10)
		->finishBuilding(true);
	EntityManager::instance()->addEntity(std::make_shared<AdvancedParticleSystem>(*aps));
	delete aps;*/

	auto b = std::make_shared<Bullet>(Bullet("Playerbullet", origin, 5, 2));
	b->setTarget(EntityManager::instance()->findEntityByName("EEE"), 1);
	EntityManager::instance()->addEntity(b);
	numberOfRounds--;
}

void PlayerCannon::update(float deltaTime)
{

}
