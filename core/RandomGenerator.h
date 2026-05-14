#ifndef MICROSOCIETY_RANDOMGENERATOR_H
#define MICROSOCIETY_RANDOMGENERATOR_H
#include <random>

class RandomGenerator {
private:
    std::mt19937 engine;

    RandomGenerator();

public:
    RandomGenerator(const RandomGenerator& other) = delete;
    RandomGenerator& operator=(const RandomGenerator& other) = delete;

    static RandomGenerator& getInstance();

    int getInt(int minValue, int maxValue);
    double getDouble(double minValue, double maxValue);
};

#endif //MICROSOCIETY_RANDOMGENERATOR_H