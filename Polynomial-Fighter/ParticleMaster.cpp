#include "ParticleMaster.h"
#include "APSBuilder.h"
#include "EntityManager.h"
#include "ParticleTrail.h"

void ParticleMaster::addPlayerShootParticles(const sf::Vector2f& position, float rotation)
{
	auto aps = APSBuilder::startBuilding(position)
		->setMainData(1000, 30)
		.setScaling(0.999f)
		.setVelocity(0.3f, 0.4f, 0.99f)
		.setIntervals(100)
		.setAsCircle(3, 16)
		.setDispersion(30, rotation - 90)
		.setColors(sf::Color(255, 255, 193), 0.2f, sf::Color::Transparent, 0, 0.005f)
		.finishBuilding(true);
	/*
	->setMainData(1000, 30)
	->setScaling(0.999f)
	->setVelocity(0.3f, 0.9f, 0.99f)
	->setIntervals(100, 50, 0)
	->setAsCircle(3, 16)
	->setDispersion(30, rotation - 90)
	->setColors(sf::Color(255, 255, 193), 0.2f, sf::Color::Transparent, 0.1f, 0.005f)
	->finishBuilding(true);
	*/
	EntityManager::instance()->addEntity(aps);

}

void ParticleMaster::addEnemyHitParticles(const sf::Vector2f &position, const sf::Vector2f &incoming, float modifier)
{
	auto aps = APSBuilder::startBuilding(position)
		->setMainData(2000, 30)
		.setIntervals(100)
		.setColors(sf::Color::Red, 0.7f, Colors::WHITE, 0.1f, 0.001f)
		.setAsCircle(3 * modifier, 6)
		.setVelocity(0.2f * modifier, 0.1f, 0.999f)
		.setScaling(0.999f)
		.setGravity(true, -incoming*0.05f)
		.setDispersion(80 / modifier, incoming)
		.finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));
	aps = APSBuilder::startBuilding(position)
		->setMainData(1500, 15)
		.setIntervals(100)
		.setColors(Colors::FIRST, 0.7f, Colors::WHITE, 0.1f, 0.002f)
		.setAsCircle(10 * modifier, 5)
		.setVelocity(0.04f * modifier, 0.1f, 0.998f)
		.setScaling(0.998f)
		.setDispersion(80 / modifier, -incoming)
		.finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));
}

void ParticleMaster::addEnemyDestroyedParticles(const sf::Vector2f& position, float modifier)
{
	auto aps = APSBuilder::startBuilding(position)
		->setMainData(4000, 50)
		.setIntervals(100)
		.setColors(Colors::FIRST, 0.1f, Colors::WHITE, 0.1f, 0.002f)
		.setAsCircle(10, 12)
		.setVelocity(0.15f*modifier, 0.1f, 0.999f)
		.setScaling(0.997f)
		.finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));
}

void ParticleMaster::addPlayerHitParticles(const sf::Vector2f &position, const sf::Vector2f &incoming, float modifier)
{
	auto aps = APSBuilder::startBuilding(position)
		->setMainData(2000, 15)
		.setIntervals(100)
		.setColors(Colors::FIRST, 0.3f, Colors::WHITE, 0.1f, 0.001f)
		.setAsCircle(4, 6)
		.setVelocity(0.4f * modifier, 0.1f, 0.999f)
		.setScaling(0.999f)
		.setDispersion(40 / modifier, incoming)
		.finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));
}

void ParticleMaster::addPlayerDestroyedParticles(const sf::Vector2f& position, float modifier)
{
	auto aps = APSBuilder::startBuilding(position)
		->setMainData(3000, 100)
		.setIntervals(100)
		.setColors(Colors::FIRST, 0.1f, Colors::WHITE, 0.0f, 0.001f)
		.setAsCircle(5, 6)
		.setVelocity(0.5f * modifier, 0.2f, 0.995f)
		.setScaling(0.999f)
		.finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));
}

std::shared_ptr<ParticleTrail> ParticleMaster::addEnemyTrail(Entity &target)
{
	auto aps = APSBuilder::startBuilding(target.getPosition())
		->setMainData(50, 150, Space::WORLD)
		.setLooping(true)
		.setColors(Colors::WHITE, 0.4f, sf::Color::Transparent, 0.0f, 0.006f)
		.setAsCircle(1, 4)
		.setVelocity(0.04f, 0.2f, 0.995f)
		.setScaling(0.996f)
		.finishBuilding();
	EntityManager::instance()->addEntity(std::shared_ptr<AdvancedParticleSystem>(aps));
	auto pt = std::make_shared<ParticleTrail>(aps, target);
	EntityManager::instance()->addEntity(pt);
	return pt;
}
