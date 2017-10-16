#ifndef POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H
#define POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H

#include <random>

using namespace std;

class RandomGenerator
{
public:
    static int getInt(int min, int max);
    static double getDouble(double min, double max);
    static int getIntGauss(int mean, double stdDev = 1.0);
    static double getDoubleGauss(double mean, double stdDev = 1.0);
};


#endif //POLYNOMIAL_FIGHTER_RANDOMGENERATOR_H
