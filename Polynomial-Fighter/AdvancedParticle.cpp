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
	/*currentShape->rotate(angularVelocity*deltaTime);
	currentShape->scale(scaling, scaling);*/
	float scaling = lerp(1.0f, this->scaling, deltaTime);
	circle.scale(scaling, scaling);

	if (useGravity)
	{
		setPosition(getPosition() + gravity * deltaTime);
	}
}

void AdvancedParticle::applyColorChange(float deltaTime)
{
	currentColor = currentColor.lerpTo(endColor, colorChangingSpeed*deltaTime, false);
	//currentShape->setFillColor(currentColor.toColor());
	circle.setFillColor(currentColor.toColor());
}

void AdvancedParticle::checkPulse()
{
	/*
	if (abs(velocity.x) < minValues::minVelocity && abs(velocity.y) < minValues::minVelocity)
	{
		isAlive = false;
		Debug::PrintFormatted("DEAD by speed");
		parent->informOfDeath();
	}
	*/

	/*if (abs(currentShape->getScale().x)<minValues::minScale &&
		abs(currentShape->getScale().y)<minValues::minScale)*/
	if (abs(circle.getScale().x) < minValues::minScale &&
		abs(circle.getScale().y) < minValues::minScale)
	{
		isAlive = false;
		Debug::PrintFormatted("DEAD by scale");
		parent->informOfDeath();
	}

	/*float f = currentColor.calculateMaxDifference(endColor, true);
	if (f < minValues::minColorDifference)
	{
		Debug::PrintFormatted("DEAD by color");
		isAlive = false;
		parent->informOfDeath();
	}*/
}

AdvancedParticle::AdvancedParticle(float radius, int pointCount, AdvancedParticleSystem *parent)
{
	this->parent = parent;

	circle = sf::CircleShape(radius, pointCount);
	circle.setOrigin(radius, radius);
	//currentShape = &circle;
}
//
//AdvancedParticle::AdvancedParticle(sf::Vector2f size, AdvancedParticleSystem *parent)
//{
//	this->parent = parent;
//
//	rectangle = sf::RectangleShape(size);
//	rectangle.setOrigin(size*0.5f);
//	currentShape = &rectangle;
//}

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
	//currentShape->setFillColor(startColor);
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
		//target.draw(*currentShape, states);
		target.draw(circle, states);
	}
}

void AdvancedParticle::update(const Time::TimeData &timeData)
{
	if (isAlive) {
		float deltaTime = std::abs(timeData.getScaledDeltaTimeInMili());
		applyTransform(deltaTime);
		applyDrag(deltaTime);
		applyColorChange(deltaTime);
		//checkPulse();
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
	return circle.getPosition();// currentShape->getPosition();
}

void AdvancedParticle::setPosition(const sf::Vector2f &position)
{
	//currentShape->setPosition(position);
	circle.setPosition(position);
}

#pragma endregion 
