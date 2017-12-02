#include "PlayerCannon.h"
#include "Bullet.h"
#include "GameData.h"
#include "APSBuilder.h"
#include "EntityManager.h"
#include "Player.h"

PlayerCannon::PlayerCannon(const sf::Vector2f &origin, Player *playerReference)
{
	this->origin = origin;
	this->playerReference = playerReference;
	state = IDLE;

	numberOfRounds = GameData::DEFAULT_NUMBER_OF_ROUNDS;
}

void PlayerCannon::appendTargets(const std::vector<DesignatedTarget>& targets)
{
	//this->targets.insert(this->targets.end(), targets.begin(), targets.end());
	for(auto &t : targets)
	{
		this->targets.push(t);
	}
	if(targets.size() == 0)
	{
		state = IDLE;
	}
	else if(state == IDLE)
	{
		currentTarget = this->targets.front();
		this->targets.pop();
		sf::Vector2f pos = EntityManager::instance()->findEntityById(currentTarget.recipientID)->getPosition();
		playerReference->setTargetPosition(pos);
	}
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
	b->setTarget(EntityManager::instance()->findEntityById(currentTarget.recipientID), 1);
	EntityManager::instance()->addEntity(b);
	numberOfRounds--;
}

void PlayerCannon::update(float deltaTime)
{

}
