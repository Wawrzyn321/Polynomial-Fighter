#include "ParticleSystem.h"

//todo change to RandomGenerator
float ParticleSystem::randomVariation(float variation) {
	if (variation <= 0) return 1;
	if (variation > 1) variation = 1;
	int v = rand() % (int)(1000.0f*variation * 2);
	return 1 - variation + v*0.001f;
}

#pragma region Building the system

ParticleSystem::ParticleSystem()
{
	tag = GameData::TAG_PARTICLE_SYSTEM;
}

ParticleSystem* ParticleSystem::startBuilding(sf::Vector2f position) {
		setPosition(position);
		amount = PSDefaultValues::amount;
		time = PSDefaultValues::time;
		dispersionAngle = PSDefaultValues::dispersionAngle;
		direction = PSDefaultValues::direction;
		startVelocity = PSDefaultValues::startVelocity;
		size = PSDefaultValues::size;

		color = cachedColor;
		sizeVariation = 0;
		velocityVariation = 0;

		accumulator = 0;

		return this;
	}

ParticleSystem* ParticleSystem::setAmount(int amount) {
	this->amount = amount;
	return this;
}

ParticleSystem * ParticleSystem::setTime(float time)
{
	this->time = time;
	return this;
}

ParticleSystem* ParticleSystem::setColor(sf::Color color) {
		this->color = color;
		return this;
	}

ParticleSystem* ParticleSystem::setSize(float size, float sizeVariation) {
		this->size = size;
		this->sizeVariation = sizeVariation;
		return this;
	}

ParticleSystem* ParticleSystem::setStartVelocity(float startVelocity, float velocityVariation) {
		this->startVelocity = startVelocity;
		this->velocityVariation = velocityVariation;
		return this;
	}

ParticleSystem* ParticleSystem::setDispersion(sf::Vector2f direction, int dispersionAngle) {
		this->direction = direction;
		this->dispersionAngle = dispersionAngle;
		return this;
	}

ParticleSystem* ParticleSystem::setRepeating(bool repeating)
{
	//todo add repeating interval
	this->repeating = repeating;
	return this;
}

ParticleSystem* ParticleSystem::setDrag(float drag)
{
	this->drag = drag;
	return this;
}

ParticleSystem ParticleSystem::finishBuilding() {
	//add particles and velocities if needed
	for (size_t i = particles.size(); i < amount; i++) {
		float currentSize = size * randomVariation(sizeVariation);
		particles.push_back(sf::CircleShape(currentSize, 12));
		particles[i].setFillColor(cachedColor);
		velocities.push_back(sf::Vector2f());
	}

	//set color
	if (cachedColor != color) {
		for (unsigned i = 0; i < amount; i++) {
			particles[i].setFillColor(color);
		}
		cachedColor = color;
	}

	//setting angle and velocity
	float baseAngle = direction == sf::Vector2f(0, 0) ? 0
		: atan2(direction.y, direction.x)*180.0f / pi;

	for (unsigned i = 0; i < amount; i++) {
		float currentAngle = 0;
		if (dispersionAngle != 0) {
			currentAngle = (baseAngle- dispersionAngle*0.5f + rand() % dispersionAngle)*pi / 180.0f;
		}
		particles[i].setPosition(getPosition());
		float currentVelocity = startVelocity * randomVariation(velocityVariation);
		velocities[i] = sf::Vector2f(cos(currentAngle), sin(currentAngle))*currentVelocity;
	}

	return *this;
}

#pragma endregion

void ParticleSystem::update(Time::TimeData timerData)
{
	float scale = (time - accumulator) / time;
	for (unsigned i = 0; i < amount; i++) {
		particles[i].move(velocities[i]*timerData.getScaledDeltaTimeInMili());
		velocities[i] *= (1 - timerData.getScaledDeltaTimeInSec() * drag);
		particles[i].setScale(scale, scale);
	}

	accumulator += timerData.getScaledDeltaTimeInSec();
	if (accumulator > time) {
		if (repeating) {
			accumulator = 0;
			//copy-paste, ale i tak to tylko dla przyk³adu, bêdzie refaktor
			float baseAngle = direction == sf::Vector2f(0, 0) ? 0
				: atan2(direction.y, direction.x)*180.0f / pi;

			for (unsigned i = 0; i < amount; i++) {
				float currentAngle = 0;
				if (dispersionAngle != 0) {
					currentAngle = (baseAngle - dispersionAngle*0.5f + rand() % dispersionAngle)*pi / 180.0f;
				}
				particles[i].setPosition(getPosition());
				float currentVelocity = startVelocity * randomVariation(velocityVariation);
				velocities[i] = sf::Vector2f(cos(currentAngle), sin(currentAngle))*currentVelocity;
			}
		}
		else {
			setEnabled(false);
		}
	}
}

void ParticleSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (unsigned i = 0; i < amount; i++) {
		target.draw(particles[i], states);
	}
}

#pragma region ITransformable implementation

void ParticleSystem::setPosition(sf::Vector2f position) {
	this->position = position;
}

sf::Vector2f ParticleSystem::getPosition()
{
	return position;
}

#pragma endregion

#pragma region Static prefabed builders

void ParticleSystem::buildOnHitParticles(ParticleSystem *particleSystem, sf::Vector2f position, sf::Vector2f direction) {
	if (particleSystem == NULL) {
		Debug::PrintErrorFormatted("ParticleSystem::buildOnHitParticles: supplied particle system was NULL!");
		return;
	}
	particleSystem->startBuilding(position)
		->setColor(sf::Color::White)
		->setAmount(10)
		->setTime(1.2f)
		->setSize(2.5f, 0.3f)
		->setStartVelocity(0.1f, 0.1f)
		->setDispersion(direction, 30)
		->finishBuilding();
}

void ParticleSystem::buildPlayerDestroyedParticles(ParticleSystem *particleSystem, sf::Vector2f position) {
	if (particleSystem == NULL) {
		Debug::PrintErrorFormatted("ParticleSystem::buildPlayerDestroyedParticles: supplied particle system was NULL!");
		return;
	}
	particleSystem->startBuilding(position)
		->setColor(sf::Color::White)
		->setSize(4, 0.6f)
		->setTime(3.5f)
		->setStartVelocity(0.3f, 0.9f)
		->setAmount(50)
		->finishBuilding();
}

void ParticleSystem::buildEnemyDestroyedParticles(ParticleSystem *particleSystem, sf::Vector2f position) {
	if (particleSystem == NULL) {
		Debug::PrintErrorFormatted("ParticleSystem::buildEnemyDestroyedParticles: supplied particle system was NULL!");
		return;
	}
	particleSystem->startBuilding(position)
		->setColor(sf::Color::Red)
		->setAmount(20)
		->setTime(2.0f)
		->setSize(3, 0.6f)
		->setStartVelocity(0.2f, 0.6f)
		->finishBuilding();
}

#pragma endregion