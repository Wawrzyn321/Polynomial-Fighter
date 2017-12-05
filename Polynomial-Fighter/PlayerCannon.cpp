#include "PlayerCannon.h"
#include "SignedBullet.h"
#include "GameData.h"
#include "APSBuilder.h"
#include "EntityManager.h"
#include "Player.h"
#include <cassert>

void PlayerCannon::updateState()
{
	if (targets.size() == 0)
	{
		state = CannonState::IDLE;
	}
	else
	{
		getNextTarget();
	}
}

void PlayerCannon::getNextTarget()
{
	assert(!targets.empty());
	state = CannonState::WAITING_FOR_AIM;
	currentTarget = targets.front();
	targets.erase(targets.begin());
	sf::Vector2f pos = EntityManager::instance()->findEntityById(currentTarget.recipientID)->getPosition();
	playerReference->setTargetPosition(pos);
}

void PlayerCannon::shoot()
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
	std::string bulletName = "Signed bullet with " +
		std::to_string(currentTarget.root) + " for " +
		std::to_string(currentTarget.recipientID);
	auto sb = std::make_shared<SignedBullet>(bulletName, origin, 5.0f, 1.0f, currentTarget.root);

	if (!EntityManager::instance()->findEntityById(currentTarget.recipientID))
	{
		Debug::PrintErrorFormatted("no to sie stac nie powinno");
	}

	sb->setTarget(EntityManager::instance()->findEntityById(currentTarget.recipientID), 1);
	EntityManager::instance()->addEntity(sb);
	numberOfRounds--;
	updateState();
}

PlayerCannon::PlayerCannon(const sf::Vector2f &origin, Player *playerReference)
{
	this->origin = origin;
	this->playerReference = playerReference;
	state = CannonState::IDLE;
	reloadAccumulator = 0;
	reloadTime = GameData::PLAYER_RELOAD_TIME;

	numberOfRounds = GameData::DEFAULT_NUMBER_OF_ROUNDS;
}

void PlayerCannon::appendTargets(const std::vector<DesignatedTarget>& targets)
{
	reloadAccumulator = reloadTime;

	//this->targets.insert(this->targets.end(), targets.begin(), targets.end());
	for(auto &t : targets)
	{
		if (std::find(this->targets.begin(), this->targets.end(), t) == this->targets.end()) {
			this->targets.push_back(t);
		}
	}
	if (state == CannonState::IDLE) {
		updateState();
	}
}

void PlayerCannon::onRotationFinished(float angle)
{
	if (numberOfRounds != 0 || true) {
		state = CannonState::WAITING_FOR_RELOAD;
		reloadAccumulator = 0;
	}
	else
	{
		targets = std::vector<DesignatedTarget>();
	}
}

void PlayerCannon::update(float deltaTime)
{
	if(state == CannonState::WAITING_FOR_AIM || state == CannonState::WAITING_FOR_RELOAD)
	{
		reloadAccumulator += deltaTime;
		if(reloadAccumulator>=reloadTime && state == CannonState::WAITING_FOR_RELOAD)
		{
			shoot();
		}
	}
}
