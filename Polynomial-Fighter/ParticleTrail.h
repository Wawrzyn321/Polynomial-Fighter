#ifndef PARTICLE_TRAIL_H
#define PARTICLE_TRAIL_H
#include "Entity.h"
#include "AdvancedParticleSystem.h"

class ParticleTrail : public Entity
{
	std::shared_ptr<AdvancedParticleSystem> connectedAPS;
	Entity &followedTransform;
public:
	ParticleTrail(std::shared_ptr<AdvancedParticleSystem> &connectedAPS, Entity &followedTransform);

	void update(const Time::TimeData& timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
	}

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

	~ParticleTrail() override;
};


#endif
