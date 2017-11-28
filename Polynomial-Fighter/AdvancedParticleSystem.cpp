#include "AdvancedParticleSystem.h"

AdvancedParticleSystem::AdvancedParticleSystem(sf::Vector2f position)
{
	this->position = position;
	mainAccumulator = 0;
	spawnedParticles = 0;
	singleSpawnTime = 0;
	state = OFF;
}

AdvancedParticleSystem* AdvancedParticleSystem::finishBuilding()
{
	for (AdvancedParticle &particle : particles)
	{
		particle.onDestroy();
	}
	particles.clear();
	if (spawningTime <= 0) {
		for (size_t i = 0; i < count; i++) {
			addParticle();
		}
		state = ONLY_UPDATING;
	}
	else
	{
		singleSpawnTime = spawningTime / static_cast<float>(count);
	}

	return this;
}

void AdvancedParticleSystem::onLiveEnded()
{
	if (looping)
	{
		revive();
	}
	else
	{
		if (actionAfterEmmision == DESTROY)
		{
			Debug::PrintFormatted("destroy");
			setToDelete(true);
		}
		else {
			state = OFF;
		}
	}
}

void AdvancedParticleSystem::addParticle()
{
	float r = RandomGenerator::getVariation(circleRadius, shapeSizeVariation);
	int pc = static_cast<int>(RandomGenerator::getVariation(circlePointCount, shapeSizeVariation));
	particles.push_back(AdvancedParticle(r, pc, this));
	particles.back().setPosition(position);

	float baseAngle = direction == sf::Vector2f(0, 0) ? 0
		: atan2(direction.y, direction.x)*180.0f / pi;
	float currentAngle = 0;
	if (dispersionAngle != 0) {
		currentAngle = (baseAngle - dispersionAngle*0.5f + rand() % static_cast<int>(dispersionAngle))*pi / 180.0f;
	}

	sf::Color color = useRandomColors ? RandomGenerator::getRandomColor() : RandomGenerator::getVariation(startColor, startColorVariation);
	particles.back().setColors(color, RandomGenerator::getVariation(endColor, endColorVariation), colorChangingSpeed);

	sf::Vector2f vel = sf::Vector2f(cos(currentAngle), sin(currentAngle)) * RandomGenerator::getVariation(startVelocity, startVelocityVariation);
	particles.back().setTransform(vel, drag, RandomGenerator::getVariation(startAngularVelocity, startAngularVelocityVariation), angularDrag, overTimeScaling);

	particles.back().setGravity(useGravity, gravity);

	aliveParticlesCount++;
}

#pragma region Handling States

void AdvancedParticleSystem::handleStartDelay(float deltaTime)
{
	mainAccumulator += deltaTime;
	if(mainAccumulator>startDelayTime)
	{
		mainAccumulator = 0;
		state = SPAWNING;
	}
}

void AdvancedParticleSystem::handleUpdatingOnly(float deltaTime)
{
	mainAccumulator += deltaTime;
	if (mainAccumulator > time)
	{
		for (AdvancedParticle &particle : particles)
		{
			particle.isAlive = false;
		}
		onLiveEnded();
		mainAccumulator = 0;
	}
}

void AdvancedParticleSystem::handleWaitingForRevival(float deltaTime)
{
	mainAccumulator += deltaTime;
	if (mainAccumulator > timeBetweenSpawn)
	{
		revive();
	}
}

void AdvancedParticleSystem::handleUpdatingParticles(Time::TimeData timeData)
{
	mainAccumulator += timeData.getScaledDeltaTimeInMili();
	for (unsigned i = 0; i < particles.size(); i++)
	{
		particles[i].update(timeData);
	}
}

void AdvancedParticleSystem::handleSpawning(float deltaTime)
{
	mainAccumulator += deltaTime;
	spawningAccumulator += deltaTime;

	while (spawningAccumulator > singleSpawnTime && count > particles.size())
	{
		addParticle();
		spawningAccumulator -= singleSpawnTime;
	}

	if (count <= particles.size())
	{
		spawningAccumulator = 0;
		state = ONLY_UPDATING;
	}
}

#pragma endregion 

void AdvancedParticleSystem::revive()
{
	state = SPAWNING;
	finishBuilding();
	for (AdvancedParticle &particle : particles)
	{
		particle.isAlive = true;
	}
	mainAccumulator = 0;
}

void AdvancedParticleSystem::informOfDeath()
{
	aliveParticlesCount--;
	if (aliveParticlesCount == 0 && state == ONLY_UPDATING)
	{
		onLiveEnded();
	}
}

#pragma region Entity Override

void AdvancedParticleSystem::update(Time::TimeData timeData)
{
	//nie switchem.
	if(state== PRE_WAITING)
	{
		handleStartDelay(timeData.getScaledDeltaTimeInMili());
	}

	if (state == WAITING)
	{
		handleWaitingForRevival(timeData.getScaledDeltaTimeInMili());
	}

	if (state == SPAWNING)
	{
		handleSpawning(timeData.getScaledDeltaTimeInMili());
	}

	if (state == ONLY_UPDATING) {
		handleUpdatingOnly(timeData.getScaledDeltaTimeInMili());
	}

	if (state != OFF) {
		handleUpdatingParticles(timeData);
	}
}

void AdvancedParticleSystem::onDestroy()
{
	for (AdvancedParticle &particle : particles)
	{
		particle.onDestroy();
	}
}

void AdvancedParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (state != OFF) {
		for (unsigned int i = 0; i < particles.size(); i++)
		{
			particles[i].draw(target, states);
		}
	}
}

#pragma endregion

#pragma region ITransformable Override

sf::Vector2f AdvancedParticleSystem::getPosition()
{
	return position;
}

void AdvancedParticleSystem::setPosition(const sf::Vector2f position)
{
	if (space == SELF) {
		sf::Vector2f shift = position - this->position;
		for (AdvancedParticle &particle : particles)
		{
			particle.move(shift);
		}
	}
	this->position = position;
}

#pragma endregion
