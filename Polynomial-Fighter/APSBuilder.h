#ifndef APS_BUILDER_H
#define APS_BUILDER_H
#include "AdvancedParticleSystem.h"

class APSBuilder
{
	float cachedTime;

	std::shared_ptr<AdvancedParticleSystem> aps;

	APSBuilder(const sf::Vector2f &position);

public:
	static APSBuilder* startBuilding(const sf::Vector2f &position);

	APSBuilder* setMainData(float time, int count, Space space = Space::SELF, ActionAfterEmmision actionAfterEmmision = ActionAfterEmmision::DESTROY);

	APSBuilder* setIntervals(float spawningTime, float timeBetweenSpawn, float startDelayTime);

	APSBuilder* setLooping(bool looping);

	APSBuilder* setAsCircle(float circleRadius, int circlePointCount);

	APSBuilder *setScaling(float overTimeScaling);

	APSBuilder *setGravity(bool useGravity, const sf::Vector2f& gravity = sf::Vector2f(0, 0.981f));

	APSBuilder* setDispersion(float dispersionAngle, const sf::Vector2f& direction);

	APSBuilder* setDispersion(float dispersionAngle, float incomingDeg);

	APSBuilder* setColors(sf::Color startColor, float startColorVariation, sf::Color endColor, float endColorVariation, float colorChangingSpeed);

	APSBuilder* setRandomColor(bool useRandomColors);

	APSBuilder* setVelocity(float startVelocity, float startVelocityVariation, float drag);

	APSBuilder* setAngularVelocity(float startAngularVelocity, float startAngularVelocityVariation, float angularDrag);

	std::shared_ptr<AdvancedParticleSystem> finishBuilding(bool playOnStart = true) const;

};

#endif