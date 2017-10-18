#include "RandomGenerator.h"

int RandomGenerator::getInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    return dis(gen);
}

double RandomGenerator::getDouble(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(min, max);

	return dis(gen);
}

float RandomGenerator::getFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);

	return dis(gen);
}

int RandomGenerator::getIntGauss(int mean, double stdDev)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(mean, stdDev);
	
    return static_cast<int>(round(dis(gen))); //http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
}

double RandomGenerator::getDoubleGauss(double mean, double stdDev)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(mean, stdDev);

    return dis(gen);
}

float RandomGenerator::getVariation(float value, float percentage)
{
	float max = value * percentage;
	float random = getFloat(0, max * 2);
	return value - max + random;
}

int RandomGenerator::getVariation(int value, float percentage)
{
	int max = static_cast<int>(value * percentage);
	return getInt(value - max, value + max);
}
