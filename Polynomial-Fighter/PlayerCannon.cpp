#include "PlayerCannon.h"
#include "SignedBullet.h"
#include "GameData.h"
#include "APSBuilder.h"
#include "EntityManager.h"
#include "Player.h"
#include <cassert>
#include "FleetingText.h"
#include "ReductionWave.h"
#include "SoundManager.h"
#include "AssetManager.h"

void PlayerCannon::updateState()
{
	if (targets.empty())
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
	std::shared_ptr<Entity> entity = {};
	while(!entity && !targets.empty())
	{
		currentTarget = targets.front();
		entity = EntityManager::instance()->findEntityById(currentTarget.recipientID);
		if (!entity)
		{
			targets.pop_back();
		}
	}
	if (entity) {
		sf::Vector2f pos = entity->getPosition();
		playerReference->setTargetPosition(pos);
	}
}

void PlayerCannon::shoot()
{
	if (!EntityManager::instance()->findEntityById(currentTarget.recipientID))
	{
		return;
	}

	targets.erase(targets.begin());
	sf::Vector2f muzzlePoint = origin + graphics->computeMuzzleShift();

	auto sb = std::make_shared<SignedBullet>(muzzlePoint, 1.0f, currentTarget.root);
	sb->name = "Signed bullet with " +
		std::to_string(currentTarget.root) + " for " +
		std::to_string(currentTarget.recipientID);

	graphics->setShoot(muzzlePoint, playerReference->getRotation());

	sb->setTarget(EntityManager::instance()->findEntityById(currentTarget.recipientID), 0.5f);
	EntityManager::instance()->addEntity(sb);
	updateState();

	SoundManager::instance()->playSound(Assets::SOUND_PLAYER_SHOOT);
}

void PlayerCannon::addAfterAppendText(int targetsAdded) const
{
	std::string caption;
	sf::Color color;
	if (targetsAdded == 0)
	{
		caption = "Miss";
		color = sf::Color(255, 233, 233);
		SoundManager::instance()->playSound(Assets::SOUND_MISS);
	}
	else if (targetsAdded == 1)
	{
		caption = "New target";
		color = sf::Color(255, 233, 233);
	}
	else {
		caption = std::to_string(targetsAdded) + " new targets";
		color = Colors::WHITE;
	}

	auto ft = std::make_shared<FleetingText>(caption, origin + sf::Vector2f(0, -20), color, 20);
	ft->run(0.001f, { RandomGenerator::getFloat(-0.01f, 0.01f), -0.03f }, 0);
	EntityManager::instance()->addEntity(ft);
}

void PlayerCannon::initGraphics()
{
	munitionContainer = std::make_shared<MunitionContainer>(
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.03f, GameData::WINDOW_SIZE.y*0.03f),
		sf::Vector2f(GameData::WINDOW_SIZE.x*0.3f, GameData::WINDOW_SIZE.y*0.08f));

	graphics = std::make_shared<PlayerCannonGraphics>();
}

PlayerCannon::PlayerCannon(Player *playerReference, const sf::Vector2f &origin)
{
	this->playerReference = playerReference;
	this->origin = origin;
	state = CannonState::IDLE;
	reloadAccumulator = 0;
	reloadTime = defaultReloadTime;
	currentTarget = DesignatedTarget();

	initGraphics();
}

void PlayerCannon::addRounds(int roundsToAdd) const
{
	munitionContainer->addRounds(roundsToAdd);
	auto ft = std::make_shared<FleetingText>("+"+std::to_string(roundsToAdd)+" rounds",
		origin + sf::Vector2f(0, -20), sf::Color(193, 255, 193), 20);
	ft->run(0.001f, { RandomGenerator::getFloat(-0.01f, 0.01f), -0.03f }, 0);
	EntityManager::instance()->addEntity(ft);
}

void PlayerCannon::appendTargets(const std::vector<int>& values, const std::vector<std::shared_ptr<Entity>> &enemies)
{
	auto shuffledValues = values;
	std::random_shuffle(shuffledValues.begin(), shuffledValues.end());

	int targetsAdded = 0;
	auto size = int(shuffledValues.size());
	if (munitionContainer->canShoot(size)) {
		munitionContainer->removeRounds(size);

		std::vector<DesignatedTarget> designatedTargets;
		for (const auto &e : enemies)
		{
			for (auto v : shuffledValues)
			{
				std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(e);
				assert(enemy);
				if (enemy->getPolynomial()->canBeDamagedBy(v))
				{
					targetsAdded++;
					designatedTargets.push_back({ enemy->getId(), v });
				}
			}
		}

		for (auto &t : designatedTargets)
		{
			bool canAddNewTarget = std::find(targets.begin(), targets.end(), t) == targets.end();

			if (canAddNewTarget) {
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
		auto ft = std::make_shared<FleetingText>("Not enough bullets!", 
			origin + sf::Vector2f(0, -20), sf::Color(255, 233, 233), 20);
		ft->run(0.001f, { RandomGenerator::getFloat(-0.01f, 0.01f), -0.03f }, 0);
		EntityManager::instance()->addEntity(ft);

		SoundManager::instance()->playSound(Assets::SOUND_NO_ROUNDS);
	}
}

void PlayerCannon::reduce(int divisor, const std::vector<std::shared_ptr<Entity>>& enemies) const
{
	if(divisor != 0)
	{
		auto rw = std::make_shared<ReductionWave>(playerReference->getPosition(), divisor, enemies);
		EntityManager::instance()->addEntity(rw);
		SoundManager::instance()->playSound(Assets::SOUND_WAVE);
	}
}

void PlayerCannon::onRotationFinished(float angle)
{
	if (munitionContainer->canShoot() != 0) {
		state = CannonState::WAITING_FOR_RELOAD;
		reloadAccumulator = 0;
	}
	else
	{
		targets = std::vector<DesignatedTarget>();
	}
}

void PlayerCannon::setPosition(const sf::Vector2f &position) const
{
	graphics->setPosition(position);
}

void PlayerCannon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	munitionContainer->draw(target, states);
	if (playerReference->getAlive()) {
		graphics->draw(target, states);
	}
}

void PlayerCannon::update(float deltaTime)
{
	munitionContainer->update(deltaTime);

	graphics->update(deltaTime, playerReference->getRotation());

	if (state == CannonState::WAITING_FOR_AIM || state == CannonState::WAITING_FOR_RELOAD)
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
	munitionContainer.reset();
}
