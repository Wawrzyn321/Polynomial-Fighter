#include "ParticleTrail.h"

ParticleTrail::ParticleTrail(std::shared_ptr<AdvancedParticleSystem> &connectedAPS,
	Entity &followedTransform) : followedTransform(followedTransform)
{
	this->followedTransform = followedTransform;
	this->connectedAPS = connectedAPS;
}

void ParticleTrail::update(const Time::TimeData& timeData)
{
	if (getToDelete() == false && getEnabled()) {
		setPosition(followedTransform.getPosition());
	}
}

sf::Vector2f ParticleTrail::getPosition() const
{
	return connectedAPS->getPosition();
}

void ParticleTrail::setPosition(const sf::Vector2f& position)
{
	return connectedAPS->setPosition(position);
}

ParticleTrail::~ParticleTrail()
{
	connectedAPS->setToDelete(true);
}
