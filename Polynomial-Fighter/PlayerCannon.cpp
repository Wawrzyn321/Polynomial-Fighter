#include "PlayerCannon.h"
#include "SignedBullet.h"
#include "GameData.h"
#include "APSBuilder.h"
#include "EntityManager.h"
#include "Player.h"
#include <cassert>
#include "FleetingText.h"

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
	auto sb = std::make_shared<SignedBullet>(origin, 5.0f, 1.0f, currentTarget.root);
	sb->name = "Signed bullet with " +
		std::to_string(currentTarget.root) + " for " +
		std::to_string(currentTarget.recipientID);

	if (!EntityManager::instance()->findEntityById(currentTarget.recipientID))
	{
		Debug::PrintErrorFormatted("no to sie stac nie powinno %", currentTarget.recipientID);
	}

	sb->setTarget(EntityManager::instance()->findEntityById(currentTarget.recipientID), 1);
	EntityManager::instance()->addEntity(sb);
	updateState();
}

void PlayerCannon::addAfterAppendText(int targetsAdded) const
{
	std::string caption;
	sf::Color color;
	if (targetsAdded == 0)
	{
		caption = "Miss";
		color = sf::Color(255, 233, 233);
	}
	else if (targetsAdded == 1)
	{
		caption = "New target";
		color = sf::Color(255, 233, 233);
	}
	else {
		caption = std::to_string(targetsAdded) + " new targets";
		color = sf::Color::White;
	}

	auto ft = std::make_shared<FleetingText>(caption, origin + sf::Vector2f(0, -20), color, 20);
	ft->run(0.001f, { RandomGenerator::getFloat(-0.01f, 0.01f), -0.03f }, 0);
	EntityManager::instance()->addEntity(ft);
}

PlayerCannon::PlayerCannon(Player *playerReference)
{
	this->playerReference = playerReference;
	origin = playerReference->getPosition();
	state = CannonState::IDLE;
	reloadAccumulator = 0;
	reloadTime = defaultReloadTime;
	currentTarget = DesignatedTarget();

	munitionGUI = std::make_shared<MunitionContainer>(sf::Vector2f(GameData::WINDOW_SIZE.x*0.03f, GameData::WINDOW_SIZE.y*0.03f),
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f ));
}

void PlayerCannon::appendTargets(const std::vector<int>& values, const std::vector<std::shared_ptr<Entity>> &enemies)
{
	auto shuffledValues = values;
	std::random_shuffle(shuffledValues.begin(), shuffledValues.end());

	int targetsAdded = 0;
	int size = int(shuffledValues.size());
	if (munitionGUI->canShoot(size)) {
		munitionGUI->removeRounds(size);

		std::vector<DesignatedTarget> designatedTargets;
		for (auto e : enemies)
		{
			for (auto v : shuffledValues)
			{
				std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(e);
				assert(enemy);
				if (enemy->canBeDamagedBy(v))
				{
					targetsAdded++;
					designatedTargets.push_back({ enemy->getId(), v });
				}
			}
		}

		for (auto &t : designatedTargets)
		{
			if (std::find(targets.begin(), targets.end(), t) == targets.end()) {
				targets.push_back(t);
			}
		}
		if (state == CannonState::IDLE) {
			reloadAccumulator = reloadTime * 2;

			updateState();
		}

		addAfterAppendText(targetsAdded);
	}
	else
	{
		Debug::PrintFormatted("Za mao: chce %\n", size);
	}
}

void PlayerCannon::onRotationFinished(float angle)
{
	if (munitionGUI->canShoot() != 0) {
		state = CannonState::WAITING_FOR_RELOAD;
		reloadAccumulator = 0;
	}
	else
	{
		targets = std::vector<DesignatedTarget>();
	}
}

void PlayerCannon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	munitionGUI->draw(target, states);
}

void PlayerCannon::update(float deltaTime)
{
	munitionGUI->update(deltaTime);
	if(state == CannonState::WAITING_FOR_AIM || state == CannonState::WAITING_FOR_RELOAD)
	{
		reloadAccumulator += deltaTime;
		if(reloadAccumulator>=reloadTime && state == CannonState::WAITING_FOR_RELOAD)
		{
			shoot();
		}
	}
}

PlayerCannon::~PlayerCannon()
{
	munitionGUI.reset();
}
