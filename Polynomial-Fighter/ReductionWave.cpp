#include "ReductionWave.h"
#include "GameData.h"
#include "Debug.h"
#include <cassert>

void ReductionWave::updateGraphics(float deltaTime)
{
	float newRadius = shape.getRadius() + deltaTime*radiusDelta;
	shape.setRadius(newRadius);
	shape.setOutlineThickness(newRadius * outlinePercentage);
	shape.setOrigin(newRadius, newRadius);
	setPosition(getPosition());
}

void ReductionWave::checkDistance()
{
	for (int i = int(enemies.size()) - 1; i >= 0; i--)
	{
		if (enemies[i].expired())
		{
			enemies.erase(enemies.begin() + i);
		}
		else {
			float sqrD = squaredDistance(enemies[i].lock()->getPosition(), getPosition());
			if (sqrD < shape.getRadius()*shape.getRadius())
			{
				if (enemies[i].lock()->getPolynomial()->canBeReducedBy(divisor))
				{
					enemies[i].lock()->getPolynomial()->reduceCoefficientsBy(divisor);
				}
				enemies.erase(enemies.begin() + i);
			}
		}
	}
}

ReductionWave::ReductionWave(sf::Vector2f& position, int divisor, std::vector<std::shared_ptr<Entity>> entities)
{
	this->divisor = divisor;

	for (std::shared_ptr<Entity> entity : entities)
	{
		std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(entity);
		assert(enemy);
		enemies.push_back(enemy);
	}

	float screenDiagonalSqr = float(GameData::WINDOW_SIZE.x*GameData::WINDOW_SIZE.x
		+ GameData::WINDOW_SIZE.y*GameData::WINDOW_SIZE.y);
	finalRadius = sqrt(screenDiagonalSqr);

	shape = sf::CircleShape(0, 64);
	shape.setFillColor(waveColor);
	shape.setOutlineColor(outlineColor);
	setPosition(position);
}

void ReductionWave::update(const Time::TimeData& timeData)
{
	if (shape.getRadius() < finalRadius)
	{
		updateGraphics(timeData.getScaledDeltaTimeInMili());

		checkDistance();
	}
	else
	{
		setToDelete(true);
	}
}

void ReductionWave::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

sf::Vector2f ReductionWave::getPosition() const
{
	return shape.getPosition();
}

void ReductionWave::setPosition(const sf::Vector2f& position)
{
	shape.setPosition(position);
}
