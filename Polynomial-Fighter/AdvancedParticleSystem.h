#ifndef ADVANCED_PARTICLE_SYSTEM_H
#define ADVANCED_PARTICLE_SYSTEM_H

#include "RandomGenerator.h"
#include "AdvancedParticle.h"
#include "AdvancedParticleSystemData.h"

class AdvancedParticleSystem : public Entity
{
	friend class APSBuilder;

	APSState state;
	sf::Vector2f position;
	std::vector<AdvancedParticle> particles;

	bool looping = false;
	float spawningTime = 2000;
	float timeBetweenSpawn = 1000;
	float startDelayTime = 0;

	int count = 20;
	float size = 5;

	float dispersionAngle = 360;
	sf::Vector2f direction = sf::Vector2f(0, 0);

	float startVelocity = 0.01f;
	float startVelocityVariation = 0.1f;
	float drag = 1;

	float startAngularVelocity = 0.0f;
	float startAngularVelocityVariation = 0.1f;
	float angularDrag = 1;

	float overTimeScaling = 0.999f;

	bool useRandomColors = false;
	sf::Color startColor = sf::Color::White;
	float startColorVariation = 0;
	sf::Color endColor = sf::Color::White;
	float endColorVariation = 0;
	float colorChangingSpeed = 1.0f;

	bool useGravity = false;
	sf::Vector2f gravity = sf::Vector2f(0, 9.81f);

	float circleRadius = 10.0f;
	int circlePointCount = 16;
	float shapeSizeVariation = 0;

	float time = 10000;

	float mainAccumulator;
	float spawningAccumulator;
	float singleSpawnTime;
	int spawnedParticles;
	int aliveParticlesCount;

	AdvancedParticleSystem(sf::Vector2f position);
	AdvancedParticleSystem* finishBuilding();

	void addParticle();

	void handleStartDelay(float get_scaled_delta_time_in_mili);
	void handleUpdatingOnly(float deltaTime);
	void handleWaitingForRevival(float deltaTime);
	void handleUpdatingParticles(Time::TimeData timeData);
	void handleSpawning(float deltaTime);
public:

	Space space = SELF;

	void revive();

	void informOfDeath();

	void update(Time::TimeData timeData) override;
	void onDestroy() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getPosition() override;
	void setPosition(const sf::Vector2f position) override;

};

#endif ADVANCED_PARTICLE_SYSTEM_H