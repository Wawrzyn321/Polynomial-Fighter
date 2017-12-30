#ifndef PARTICLE_MASTER_H
#define PARTICLE_MASTER_H
#include <SFML/System/Vector2.hpp>
#include <memory>
#include "Entity.h"
#include "ParticleTrail.h"

class ParticleMaster
{
public:
	static void addPlayerShootParticles(const sf::Vector2f& position, float rotation);

	static void addEnemyHitParticles(const sf::Vector2f& position, const sf::Vector2f& incoming, float modifier);

	static void addEnemyDestroyedParticles(const sf::Vector2f &position, float modifier);

	static void addPlayerHitParticles(const sf::Vector2f &position, const sf::Vector2f &incoming, float modifier);

	static void addPlayerDestroyedParticles(const sf::Vector2f& position, float modifier);

	static std::shared_ptr<ParticleTrail> addEnemyTrail(Entity &target);
};

#endif
