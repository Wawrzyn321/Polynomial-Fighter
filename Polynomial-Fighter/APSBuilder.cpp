#include "APSBuilder.h"

RawAPS* APSBuilder::startBuilding(sf::Vector2f position)
{
	RawAPS *rawAPS = new RawAPS(position);

	rawAPS->aps->name = "Particle System";

	return rawAPS;
}

RawAPS::RawAPS(sf::Vector2f position)
{
	aps = new AdvancedParticleSystem(position);
	cachedTime = 0;
}

RawAPS* RawAPS::setMainData(float time, int count, Space space)
{
	aps->time = time;
	aps->count = count;
	aps->space = space;

	cachedTime = time;
	return this;
}

RawAPS* RawAPS::setIntervals(float spawningTime, float timeBetweenSpawn, float startDelayTime)
{
	aps->spawningTime = spawningTime;
	aps->timeBetweenSpawn = timeBetweenSpawn;
	aps->time = cachedTime + spawningTime;
	aps->startDelayTime = startDelayTime;
	return this;
}

RawAPS* RawAPS::setLooping(bool looping)
{
	aps->looping = looping;
	return this;
}

RawAPS* RawAPS::setAsCircle(float circleRadius, int circlePointCount)
{
	aps->circleRadius = circleRadius;
	aps->circlePointCount = circlePointCount;

	//aps->shapeType = CIRCLE;
	return this;
}
//
//RawAPS* RawAPS::setAsRectangle(sf::Vector2f rectangleSize, float shapeSizeVariation, bool uniformShapeScaling)
//{
//	aps->rectangleSize = rectangleSize;
//	aps->shapeSizeVariation = shapeSizeVariation;
//	aps->uniformShapeScaling = uniformShapeScaling;
//
//	aps->shapeType = RECTANGLE;
//	return this;
//}

RawAPS* RawAPS::setScaling(float overTimeScaling)
{
	aps->overTimeScaling = overTimeScaling;
	return this;
}

RawAPS* RawAPS::setGravity(bool useGravity, sf::Vector2f gravity)
{
	aps->useGravity = useGravity;
	aps->gravity = gravity;
	return this;
}

RawAPS* RawAPS::setDispersion(float dispersionAngle, sf::Vector2f direction)
{
	aps->dispersionAngle = dispersionAngle;
	aps->direction = direction;
	return this;
}

RawAPS* RawAPS::setColors(sf::Color startColor, float startColorVariation, sf::Color endColor, float endColorVariation, float colorChangingSpeed)
{
	aps->startColor = startColor;
	aps->startAngularVelocityVariation = startColorVariation;
	aps->endColor = endColor;
	aps->endColorVariation = endColorVariation;
	aps->colorChangingSpeed = colorChangingSpeed;
	return this;
}

RawAPS* RawAPS::setRandomColor(bool useRandomColors)
{
	aps->useRandomColors = useRandomColors;
	return this;
}

RawAPS* RawAPS::setVelocity(float startVelocity, float startVelocityVariation, float drag)
{
	aps->startVelocity = startVelocity;
	aps->startVelocityVariation = startVelocityVariation;
	aps->drag = drag;
	return this;
}

RawAPS* RawAPS::setAngularVelocity(float startAngularVelocity, float startAngularVelocityVariation, float angularDrag)
{
	aps->startAngularVelocity = startAngularVelocity;
	aps->startAngularVelocityVariation = startAngularVelocityVariation;
	aps->angularDrag = angularDrag;
	return this;
}

AdvancedParticleSystem* RawAPS::finishBuilding(bool playOnStart)
{
	aps->finishBuilding();
	aps->state = PRE_WAITING;
	return aps;
}
