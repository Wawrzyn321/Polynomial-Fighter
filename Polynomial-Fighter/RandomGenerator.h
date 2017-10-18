#ifndef POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H
#define POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H

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
};


#endif //POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H
