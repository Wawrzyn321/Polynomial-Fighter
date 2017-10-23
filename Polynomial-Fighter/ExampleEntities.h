#ifndef EXAMPLE_ENTITIES_H
#define EXAMPLE_ENTITIES_H

#include "Entity.h"

class EllipseWalker : public Entity
{
	sf::CircleShape sprite;
	sf::Vector2f center;
	sf::Vector2f radii;
	float speed;

	float currentAngle;
public:
	EllipseWalker(sf::Vector2f center, sf::Vector2f semiAxes, float speed)
	{
		this->center = center;
		this->radii = semiAxes;
		this->speed = speed;
		sprite = sf::CircleShape(10, 32);
		sprite.setOrigin(5, 5);

		currentAngle = 0;
		name = "Ellipse Walker";

	}

	sf::Vector2f getPosition() override
	{
		return sprite.getPosition();
	};

	void setPosition(const sf::Vector2f position) override
	{
		sprite.setPosition(position);
	};

	void update(Time::TimeData timeData) override
	{
		currentAngle += timeData.getScaledDeltaTimeInSec()*speed;

		float x = center.x + radii.x*cos(currentAngle);
		float y = center.y + radii.y*sin(currentAngle);
		setPosition({ x,y });
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	};
};

class ColorChanger : public Entity
{
	sf::RectangleShape rect;
	float deltaSpeed;
	float value;

public:
	ColorChanger(sf::Vector2f pos, float deltaSpeed)
	{
		this->deltaSpeed = deltaSpeed;

		rect = sf::RectangleShape({ 50,50 });
		rect.setPosition(pos);

		value = 0;

		name = "Color Changer";
	}

	sf::Vector2f getPosition() override
	{
		return rect.getPosition();
	};

	void setPosition(const sf::Vector2f position) override
	{
		rect.setPosition(position);
	};

	void update(Time::TimeData timeData) override
	{
		value += timeData.getScaledDeltaTimeInSec()*deltaSpeed;

		sf::Uint8 v = static_cast<sf::Uint8>((sin(value) + 1) * 0.5f * 255);

		rect.setFillColor(sf::Color(255 - v, v, v));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(rect, states);
	};
};

class TransformObserver : public Entity
{
	sf::RectangleShape rect;
	std::shared_ptr<ITransformable> observed;

public:
	TransformObserver(sf::Vector2f pos, const std::weak_ptr<Entity> observed)
	{
		this->observed = observed.lock();

		rect = sf::RectangleShape({ 100,20 });
		rect.setPosition(pos);
		rect.setOrigin(50, 10);

		name = "Transform Observer";
	}

	sf::Vector2f getPosition() override
	{
		return rect.getPosition();
	};

	void setPosition(const sf::Vector2f position) override
	{
		rect.setPosition(position);
	};

	void update(Time::TimeData timeData) override
	{
		sf::Vector2f diff = observed->getPosition() - getPosition();

		double angle = atan2(diff.y, diff.x);
		angle *= 180 / 3.1415926535;

		rect.setRotation(static_cast<float>(angle));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(rect, states);
	};
};


class EmergencyBlinker : public Entity
{
	sf::CircleShape circle;
	float accumulator;
	float timeInMS;

public:
	EmergencyBlinker(sf::Vector2f pos, float timeInMS)
	{
		this->timeInMS = timeInMS;

		circle = sf::CircleShape(30, 32);
		circle.setPosition(pos);
		circle.setFillColor(sf::Color::Blue);

		accumulator = 0;
		name = "Ticking Entity";
	}

	sf::Vector2f getPosition() override
	{
		return circle.getPosition();
	};

	void setPosition(const sf::Vector2f position) override
	{
		circle.setPosition(position);
	};

	void update(Time::TimeData timeData) override
	{
		accumulator += timeData.getScaledDeltaTimeInMili();
		if (accumulator > timeInMS)
		{
			flash();
			accumulator -= timeInMS;
		}
	}

	void flash()
	{
		circle.setFillColor(circle.getFillColor() == sf::Color::Red ? sf::Color::Blue : sf::Color::Red);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(circle, states);
	};
};

#endif