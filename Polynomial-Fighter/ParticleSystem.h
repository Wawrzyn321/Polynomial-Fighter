#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_h

#include <vector>
#include "Entity.h"

namespace PSDefaultValues {
	const unsigned amount = 20;
	const float time = 2.0f;
	const int dispersionAngle = 360;
	const sf::Vector2f direction = sf::Vector2f(0, 0);
	const float startVelocity = 0.1f;
	const float size = 5;
};


class ParticleSystem : public Entity {
private:
	std::vector<sf::CircleShape> particles;
	std::vector<sf::Vector2f> velocities;

	sf::Vector2f position;
	unsigned amount;

	float startVelocity;
	float velocityVariation;

	float size;
	float sizeVariation;

	float accumulator;
	float time;

	int dispersionAngle;
	sf::Vector2f direction;

	sf::Color color;

	sf::Color cachedColor = sf::Color::White;

	float randomVariation(float variation);

public:
	ParticleSystem();

	ParticleSystem* startBuilding(sf::Vector2f position);

	ParticleSystem *setAmount(int amount);

	ParticleSystem *setTime(float time);

	ParticleSystem* setColor(sf::Color color);

	ParticleSystem* setSize(float size, float sizeVariation = 0);

	ParticleSystem* setStartVelocity(float startVelocity, float velocityVariation = 0);

	ParticleSystem* setDispersion(sf::Vector2f direction, int dispersionAngle);

	ParticleSystem finishBuilding();

	void update(Time::TimeData timerData);

	void draw(sf::RenderTarget & target, sf::RenderStates states = sf::RenderStates::Default) const;

	void setPosition(sf::Vector2f position);

	sf::Vector2f getPosition();

	static void buildOnHitParticles(ParticleSystem *particleSystem, sf::Vector2f position, sf::Vector2f direction);

	static void buildPlayerDestroyedParticles(ParticleSystem *particleSystem, sf::Vector2f position);

	static void buildEnemyDestroyedParticles(ParticleSystem *particleSystem, sf::Vector2f position);
};

#endif