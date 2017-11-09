#ifndef POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H
#define POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H

#include "Utility.h"
#include <random>

class RandomGenerator
{
public:
    static int getInt(int min, int max);
	static double getDouble(double min, double max);
	static float getFloat(float min, float max);
    static int getIntGauss(int mean, double stdDev = 1.0);
    static double getDoubleGauss(double mean, double stdDev = 1.0);
	static float getVariation(float value, float percentage);
	static int getVariation(int value, float percentage);
	static sf::Color getRandomColor(bool includeAlpha = false);
	static sf::Color getVariation(sf::Color color, float variation, bool includeAlpha = false);

	template<typename T>
	static sf::Vector2<T> getVariation(sf::Vector2<T> v, float variation, bool uniform = true)
	{
		if (uniform)
		{
			float value = getVariation(1.0f, variation);
			return value*v;
		}
		else
		{
			float valueX = getVariation(1.0f, variation);
			float valueY = getVariation(1.0f, variation);
			return { v.x*valueX, v.y*valueY };
		}
	}
};


#endif //POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H
