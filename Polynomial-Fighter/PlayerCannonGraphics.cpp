#include "PlayerCannonGraphics.h"
#include "Utility.h"
#include "AssetManager.h"
#include "ParticleMaster.h"

PlayerCannonGraphics::PlayerCannonGraphics()
{
	font = AssetManager::instance()->getDefaultFont();
	cannon = sf::Text("f", *font, fontSize);
	centerTextOrigin(cannon);
	cannon.setOrigin(cannon.getOrigin() - computeMuzzleShift());

	rotationAngleModifier = 0;
}

sf::Vector2f PlayerCannonGraphics::computeMuzzleShift() const
{
	float angle = (cannon.getRotation() + 190) * pi / 180.0f;

	float cosine = cos(angle);
	float sine = sin(angle);

	float length = fontSize * 0.91f;

	return { cosine*length, sine*length };
}

void PlayerCannonGraphics::setShoot(const sf::Vector2f &position, float rotation)
{
	ParticleMaster::addPlayerShootParticles(position, rotation);
	
	rotationAngleModifier = startingRotationAngleModifier;
}

void PlayerCannonGraphics::setFillColor(const sf::Color& color)
{
	cannon.setFillColor(color);
}

void PlayerCannonGraphics::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cannon, states);
}

void PlayerCannonGraphics::update(float deltaTime, float rotation)
{
	if (rotationAngleModifier != 0)
	{
		rotation += rotationAngleModifier;
		rotationAngleModifier = lerp(rotationAngleModifier, 0.0f, deltaTime*0.004f);
		if (abs(rotationAngleModifier) < minAngleDifference)
		{
			rotationAngleModifier = 0;
		}
	}

	if (abs(rotationAngleModifier) > 0.01f)
	{
		rotateTowards(cannon, rotation, deltaTime*rotationSpeed);
	}
	else
	{
		cannon.setRotation(rotation);
	}
}

void PlayerCannonGraphics::setPosition(const sf::Vector2f &position)
{
	cannon.setPosition(position);
}
