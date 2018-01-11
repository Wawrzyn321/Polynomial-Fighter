#ifndef GUI_RING_H
#define GUI_RING_H
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "Timer.h"
#include "Utility.h"

struct RingValues
{
	float radius;
	sf::Vector2f center;

	RingValues(float radius, const sf::Vector2f &center)
	{
		this->radius = radius * GameData::WINDOW_SIZE.y*0.9f;
		this->center = { center.x * GameData::WINDOW_SIZE.x , center.y*GameData::WINDOW_SIZE.y };
	}

	bool lerpBody(sf::CircleShape &shape, float deltaTime) const
	{
		bool scalingEnded = false;
		bool movingEnded = false;

		float newRadius = lerp(shape.getRadius(), radius, deltaTime*lerpSpeed);
		shape.setRadius(newRadius);
		shape.setOutlineThickness(newRadius*outlineThickness);
		shape.setOrigin(newRadius, newRadius);
		if (abs(newRadius - radius) < lerpThreshold)
		{
			scalingEnded = true;
		}

		sf::Vector2f newPos = lerp(shape.getPosition(), center, deltaTime*lerpSpeed);
		shape.setPosition(newPos);
		if (abs(newPos.x - center.x) < lerpThreshold && newPos.y - center.y < lerpThreshold){
			movingEnded = true;
		}
		return scalingEnded && movingEnded;
	}

	void finish(sf::CircleShape &shape) const
	{
		lerpBody(shape, 1.0f);
	}
private:
	const float lerpSpeed = 0.007f;
	const float lerpThreshold = 0.1f;
	const float outlineThickness = 0.1f;
};

class GUIRing : public sf::Drawable
{
public:
	enum class State
	{
		IDLE,
		TO_MINOR,
		TO_MAJOR,
		EXITING,
		TO_GAME,
		TO_MEDIUM,
		TO_RIGHT_MEDIUM,
	};
private:
	sf::CircleShape shape;
public:
	State state;

	GUIRing(const sf::Vector2f &center);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	RingValues minorValues = {
		0.44f,
		sf::Vector2f(0.5f , 0.5f),
	};
	RingValues majorValues = {
		1.07f,
		sf::Vector2f(0.5f, 1.71875f),
	};
	RingValues exitingValues = {
		0.0f,
		sf::Vector2f(0.5f, 0.5f),
	};
	RingValues toGameValues = {
		0.25f,
		sf::Vector2f(0.5f, 0.5f),
	};
	RingValues toRightMediumValues = {
		0.4f,
		sf::Vector2f(0.7f, 0.5f),
	};
	RingValues toMediumValues = {
		0.35f,
		sf::Vector2f(0.5f, 0.6f),
	};

	const float initialRadius = 1.0f;
};

#endif