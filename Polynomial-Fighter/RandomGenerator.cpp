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

int RandomGenerator::getIntGauss(int mean, double stdDev )
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(mean, stdDev);

    return round(dis(gen)); //http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
}

double RandomGenerator::getDoubleGauss(double mean, double stdDev)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(mean, stdDev);

    return dis(gen);
}