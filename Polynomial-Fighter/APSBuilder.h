#ifndef APS_BUILDER_H
#define APS_BUILDER_H
#include "AdvancedParticleSystem.h"

class RawAPS
{
	friend class APSBuilder;

	float cachedTime;

	AdvancedParticleSystem* aps = nullptr;
public:

	RawAPS(sf::Vector2f position);

	RawAPS* setMainData(float time, int count, Space space = SELF);

	RawAPS* setIntervals(float spawningTime, float timeBetweenSpawn, float startDelayTime);

	RawAPS* setLooping(bool looping);

	RawAPS* setAsCircle(float circleRadius, int circlePointCount);

	//RawAPS* setAsRectangle(sf::Vector2f rectangleSize, float shapeSizeVariation, bool uniformShapeScaling);

	RawAPS *setScaling(float overTimeScaling);

	RawAPS *setGravity(bool useGravity, sf::Vector2f gravity = sf::Vector2f(0, 0.981f));

	RawAPS* setDispersion(float dispersionAngle, sf::Vector2f direction);

	RawAPS* setColors(sf::Color startColor, float startColorVariation, sf::Color endColor, float endColorVariation, float colorChangingSpeed);

	RawAPS* setRandomColor(bool useRandomColors);

	RawAPS* setVelocity(float startVelocity, float startVelocityVariation, float drag);

	RawAPS* setAngularVelocity(float startAngularVelocity, float startAngularVelocityVariation, float angularDrag);

	AdvancedParticleSystem* finishBuilding(bool playOnStart = true);

};

class APSBuilder
{

	APSBuilder() = default;
public:
	static RawAPS* startBuilding(sf::Vector2f position);
};

#endif