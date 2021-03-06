#include "APSBuilder.h"
#include "Utility.h"

std::shared_ptr<APSBuilder> APSBuilder::startBuilding(const sf::Vector2f &position)
{
	auto builder = std::make_shared<APSBuilder>(position);

	builder->aps->name = GameData::NAME_PARTICLE_SYSTEM;

	return builder;
}

APSBuilder::APSBuilder(const sf::Vector2f &position)
{
	aps = std::make_shared<AdvancedParticleSystem>(position);
	cachedTime = 0;
}

APSBuilder & APSBuilder::setMainData(float time, int count, Space space, ActionAfterEmmision actionAfterEmmision)
{
	aps->time = time;
	aps->count = count;
	aps->space = space;
	aps->actionAfterEmmision = actionAfterEmmision;

	cachedTime = time;
	return *this;
}

APSBuilder & APSBuilder::setIntervals(float spawningTime, float timeToRevival)
{
	aps->spawningTime = spawningTime;
	aps->timeToRevival = timeToRevival;
	aps->time = cachedTime + spawningTime;
	return *this;
}

APSBuilder & APSBuilder::setLooping(bool looping)
{
	aps->looping = looping;
	return *this;
}

APSBuilder & APSBuilder::setAsCircle(float circleRadius, int circlePointCount, float radiusVariation)
{
	aps->circleRadius = circleRadius;
	aps->circlePointCount = circlePointCount;
	aps->radiusVariation = radiusVariation;
	return *this;
}

APSBuilder & APSBuilder::setScaling(float overTimeScaling)
{
	aps->overTimeScaling = overTimeScaling;
	return *this;
}

APSBuilder & APSBuilder::setGravity(bool useGravity, const sf::Vector2f &gravity)
{
	aps->useGravity = useGravity;
	aps->gravity = gravity;
	return *this;
}

APSBuilder & APSBuilder::setDispersion(float dispersionAngle, const sf::Vector2f &direction)
{
	aps->dispersionAngle = dispersionAngle;
	aps->direction = direction;
	return *this;
}

APSBuilder & APSBuilder::setDispersion(float dispersionAngle, float incomingDeg)
{
	aps->dispersionAngle = dispersionAngle;
	float angleRad = incomingDeg * pi / 180.0f;
	aps->direction = { cosf(angleRad),sinf(angleRad) };
	return *this;
}

APSBuilder & APSBuilder::setColors(const sf::Color &startColor, float startColorVariation, const sf::Color &endColor, float endColorVariation, float colorChangingSpeed)
{
	aps->startColor = startColor;
	aps->startAngularVelocityVariation = startColorVariation;
	aps->endColor = endColor;
	aps->endColorVariation = endColorVariation;
	aps->colorChangingSpeed = colorChangingSpeed;
	return *this;
}

APSBuilder & APSBuilder::setRandomColor(bool useRandomColors)
{
	aps->useRandomColors = useRandomColors;
	return *this;
}

APSBuilder & APSBuilder::setVelocity(float startVelocity, float startVelocityVariation, float drag)
{
	aps->startVelocity = startVelocity;
	aps->startVelocityVariation = startVelocityVariation;
	aps->drag = drag;
	return *this;
}

APSBuilder & APSBuilder::setAngularVelocity(float startAngularVelocity, float startAngularVelocityVariation, float angularDrag)
{
	aps->startAngularVelocity = startAngularVelocity;
	aps->startAngularVelocityVariation = startAngularVelocityVariation;
	aps->angularDrag = angularDrag;
	return *this;
}

std::shared_ptr<AdvancedParticleSystem> APSBuilder::finishBuilding(bool playOnStart)
{
	aps->finishBuilding();
	if (playOnStart) {
		aps->state = APSState::SPAWNING;
	}
	else
	{
		aps->state = APSState::OFF;
	}
	return aps;
}
