#include "AdvancedParticle.h"
#include "AdvancedParticleSystem.h"

void AdvancedParticle::applyDrag(float deltaTime)
{
	velocity *= lerp(1.0f, drag, deltaTime);
	angularVelocity *= lerp(1.0f, angularDrag, deltaTime);
}

void AdvancedParticle::applyTransform(float deltaTime)
{
	setPosition(getPosition() + velocity*deltaTime);
	float currentScaling = lerp(1.0f, scaling, deltaTime);
	circle.scale(currentScaling, currentScaling);

	if (useGravity)
	{
		setPosition(getPosition() + gravity * deltaTime);
	}
}

void AdvancedParticle::applyColorChange(float deltaTime)
{
	currentColor = currentColor.lerpTo(endColor, colorChangingSpeed*deltaTime, false);
	circle.setFillColor(currentColor.toColor());
}

void AdvancedParticle::checkPulse()
{
	if (std::fabs(velocity.x) < minValues::minVelocity && std::fabs(velocity.y) < minValues::minVelocity)
	{
		isAlive = false;
		//Debug::PrintFormatted("DEAD by speed");
		parent->informOfDeath();
	}

	if (std::fabs(circle.getScale().x) < minValues::minScale &&
        std::fabs(circle.getScale().y) < minValues::minScale)
	{
		isAlive = false;
		//Debug::PrintFormatted("DEAD by scale");
		parent->informOfDeath();
	}

	if(currentColor.calculateMaxDifference(endColor, true) < minValues::minColorDifference) {
		isAlive = false;
		//Debug::PrintFormatted("DEAD by color");
		parent->informOfDeath();
	}
}

AdvancedParticle::AdvancedParticle(float radius, int pointCount, AdvancedParticleSystem *parent)
{
	this->parent = parent;
	isAlive = true;

	circle = sf::CircleShape(radius, static_cast<size_t>(pointCount));
	circle.setOrigin(radius, radius);
}

#pragma region Setting values

void AdvancedParticle::setTransform(const sf::Vector2f &velocity, float drag, float angularVelocity, float angularDrag, float scaling)
{
	this->velocity = velocity;
	this->drag = drag;
	this->angularVelocity = angularVelocity;
	this->angularDrag = angularDrag;
	this->scaling = scaling;
}

void AdvancedParticle::setColors(const sf::Color &startColor, const sf::Color &endColor, float colorChangingSpeed)
{
	circle.setFillColor(startColor);
	this->currentColor = FloatColor(startColor);
	this->endColor = FloatColor(endColor);
	this->colorChangingSpeed = colorChangingSpeed;
}

void AdvancedParticle::setGravity(bool useGravity, const sf::Vector2f &gravity)
{
	this->useGravity = useGravity;
	this->gravity = gravity;
}

#pragma endregion 

#pragma region Entity Override

void AdvancedParticle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isAlive) {
		target.draw(circle, states);
	}
}

void AdvancedParticle::update(const Time::TimeData &timeData)
{
	if (isAlive) {
		float deltaTime = std::fabs(timeData.getScaledDeltaTimeInMili());
		applyTransform(deltaTime);
		applyDrag(deltaTime);
		applyColorChange(deltaTime);
		checkPulse();
	}
}

void AdvancedParticle::onDestroy() {}

#pragma endregion

#pragma region ITransformable Override + move function

void AdvancedParticle::move(const sf::Vector2f &shift)
{
	setPosition(getPosition() + shift);
}

sf::Vector2f AdvancedParticle::getPosition() const
{
	return circle.getPosition();
}

void AdvancedParticle::setPosition(const sf::Vector2f &position)
{
	circle.setPosition(position);
}

#pragma endregion 
