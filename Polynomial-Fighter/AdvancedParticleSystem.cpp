#include "AdvancedParticleSystem.h"

AdvancedParticleSystem::AdvancedParticleSystem(const sf::Vector2f &position)
{
	this->position = position;
	mainAccumulator = 0;
	spawnedParticles = 0;
	singleSpawnTime = 0;
	spawningAccumulator = 0;
	aliveParticlesCount = 0;
	state = APSState::OFF;
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
		state = APSState::ONLY_UPDATING;
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
		if (actionAfterEmmision == ActionAfterEmmision::DESTROY)
		{
			setToDelete(true);
		}
		else {
			state = APSState::OFF;
		}
	}
}

void AdvancedParticleSystem::addParticle()
{
	float r = RandomGenerator::getVariation(circleRadius, shapeSizeVariation);
	int pc = static_cast<int>(RandomGenerator::getVariation(circlePointCount, shapeSizeVariation));
	particles.push_back(AdvancedParticle(r, pc, this));
	AdvancedParticle &currentParticle = particles.back();
	currentParticle.setPosition(position);

	float baseAngle = direction == sf::Vector2f(0, 0) ? 0
		: atan2(direction.y, direction.x)*180.0f / pi;
	float currentAngle = 0;
	if (dispersionAngle != 0) {
		currentAngle = (baseAngle - dispersionAngle*0.5f + rand() % static_cast<int>(dispersionAngle))*pi / 180.0f;
	}

	sf::Color color = useRandomColors ? RandomGenerator::getRandomColor() : RandomGenerator::getVariation(startColor, startColorVariation);
	currentParticle.setColors(color, RandomGenerator::getVariation(endColor, endColorVariation), colorChangingSpeed);

	sf::Vector2f vel = sf::Vector2f(cos(currentAngle), sin(currentAngle)) * RandomGenerator::getVariation(startVelocity, startVelocityVariation);
	currentParticle.setTransform(vel, drag, RandomGenerator::getVariation(startAngularVelocity, startAngularVelocityVariation), angularDrag, overTimeScaling);

	currentParticle.setGravity(useGravity, gravity);

	aliveParticlesCount++;
}

#pragma region Handling States

void AdvancedParticleSystem::handleStartDelay(float deltaTime)
{
	mainAccumulator += deltaTime;
	if(mainAccumulator>startDelayTime)
	{
		mainAccumulator = 0;
		state = APSState::SPAWNING;
	}
}

void AdvancedParticleSystem::handleUpdatingOnly(float deltaTime)
{
	mainAccumulator += deltaTime;
	if (mainAccumulator > time)
	{
		//Debug::PrintFormatted("% %\n", mainAccumulator, deltaTime);
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

void AdvancedParticleSystem::handleUpdatingParticles(const Time::TimeData &timeData)
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
		state = APSState::ONLY_UPDATING;
	}
}

#pragma endregion 

void AdvancedParticleSystem::revive()
{
	state = APSState::SPAWNING;
	finishBuilding();
	for (AdvancedParticle &particle : particles)
	{
		particle.isAlive = true;
	}
	mainAccumulator = 0;
}

void AdvancedParticleSystem::informOfDeath()
{
	Debug::PrintFormatted("% ", aliveParticlesCount);
	aliveParticlesCount--;
	if (aliveParticlesCount == 0 && state == APSState::ONLY_UPDATING)
	{
		onLiveEnded();
	}
}

#pragma region Entity Override

void AdvancedParticleSystem::update(const Time::TimeData &timeData)
{
	//nie switchem.
	if(state == APSState::PRE_WAITING)
	{
		handleStartDelay(timeData.getScaledDeltaTimeInMili());
	}

	if (state == APSState::WAITING)
	{
		handleWaitingForRevival(timeData.getScaledDeltaTimeInMili());
	}

	if (state == APSState::SPAWNING)
	{
		handleSpawning(timeData.getScaledDeltaTimeInMili());
	}

	if (state == APSState::ONLY_UPDATING) {
		handleUpdatingOnly(timeData.getScaledDeltaTimeInMili());
	}

	if (state != APSState::OFF) {
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
	if (state != APSState::OFF) {
		for (unsigned int i = 0; i < particles.size(); i++)
		{
			particles[i].draw(target, states);
		}
	}
}

#pragma endregion

#pragma region ITransformable Override

sf::Vector2f AdvancedParticleSystem::getPosition() const
{
	return position;
}

void AdvancedParticleSystem::setPosition(const sf::Vector2f &position)
{
	if (space == Space::SELF) {
		sf::Vector2f shift = position - this->position;
		for (AdvancedParticle &particle : particles)
		{
			particle.move(shift);
		}
	}
	this->position = position;
}

#pragma endregion
