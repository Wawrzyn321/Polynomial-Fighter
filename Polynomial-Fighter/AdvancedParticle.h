#ifndef ADVANCED_PARTICLE_H
#define ADVANCED_PARTICLE_H

#include "Entity.h"
#include "AdvancedParticleSystemData.h"
#include "FloatColor.h"

namespace minValues
{
	const float minVelocity = 0.0001f;
	const float minColorDifference = 0.008f;
	const float minScale = 0.001f;
}

class AdvancedParticleSystem;
class AdvancedParticle : Entity
{
	sf::CircleShape circle;
	sf::Shape* currentShape;

	AdvancedParticleSystem *parent;

	sf::Vector2f velocity;
	float drag;
	float angularVelocity;
	float angularDrag;
	float scaling;
	float colorChangingSpeed;

	bool useGravity;
	sf::Vector2f gravity;

	FloatColor currentColor;
	FloatColor endColor;

	void applyDrag(float deltaTime);
	void applyTransform(float deltaTime);
	void applyColorChange(float deltaTime);
	void checkPulse();

	AdvancedParticle() {}
public:
	bool isAlive;

	AdvancedParticle(float radius, int pointCount, AdvancedParticleSystem *parent);

	//AdvancedParticle(sf::Vector2f size, AdvancedParticleSystem *parent);

	void setTransform(sf::Vector2f velocity, float drag, float angularVelocity, float angularDrag, float scaling);
	void setColors(sf::Color startColor, sf::Color endColor, float colorChangingSpeed);
	void setGravity(bool useGravity, sf::Vector2f gravity);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(Time::TimeData timeData) override;
	void onDestroy() override;

	void move(sf::Vector2f shift);
	sf::Vector2f getPosition() override;
	void setPosition(sf::Vector2f position) override;

};

#endif