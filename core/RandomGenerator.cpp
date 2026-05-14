#include "RandomGenerator.h"
#include <algorithm>

RandomGenerator::RandomGenerator()
    : engine(std::random_device{}()) {}

RandomGenerator& RandomGenerator::getInstance() {
    static RandomGenerator instance;
    return instance;
}

int RandomGenerator::getInt(int minValue, int maxValue) {
    if (minValue > maxValue) {
        std::swap(minValue, maxValue);
    }

    std::uniform_int_distribution<int> distribution(minValue, maxValue);
    return distribution(engine);
}

double RandomGenerator::getDouble(double minValue, double maxValue) {
    if (minValue > maxValue) {
        std::swap(minValue, maxValue);
    }

    std::uniform_real_distribution<double> distribution(minValue, maxValue);
    return distribution(engine);
}