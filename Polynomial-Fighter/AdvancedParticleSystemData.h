#ifndef ADVANCED_PARTICLE_SYSTEM_DATA_H
#define ADVANCED_PARTICLE_SYSTEM_DATA_H

#include <SFML/Graphics.hpp>

enum class Space
{
	SELF,
	WORLD,
};

enum class ActionAfterEmmision
{
	DEACTIVATE,
	DESTROY,
};

enum class APSState
{
	PRE_WAITING,
	SPAWNING,
	ONLY_UPDATING,
	WAITING,
	OFF,
};

namespace APSDefaultValues {

	//main data
	const unsigned amount = 20;
	const bool animateInWorldSpace = true;
	const bool repeating = false;

	//time
	const float spawningTime = 2000;
	const float timeBetweenSpawn = 1000;
	const float time = 2.0f;

	//dispersion
	const float dispersionAngle = 360;
	const sf::Vector2f direction = sf::Vector2f(0, 0);

	//speed
	const float startSpeed = 0.01f;
	const float startSpeedVariation = 0.1f;
	const float drag = 1;

	//scaling
	const float scaling = 0.99f;

	//angular speed
	const float startAngularVelocity = 0.0f;
	const float startAngularVelocityVariation = 0.1f;
	const float angularDrag = 1;

	//gravity
	const bool useGravity = false;
	const sf::Vector2f gravity = sf::Vector2f(0, 0.0981f);

	//colors
	const bool useRandomColors = false;
	const sf::Color startColor = sf::Color::White;
	const float startColorVariation = 0;
	const sf::Color endColor = sf::Color::White;
	const float endColorVariation = 0;
	const float colorChangingSpeed = 1.0f;

	//as circle
	const float circleRadius = 10.0f;
	const float circlePointCount = 16;

}

#endif