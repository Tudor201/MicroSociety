#include "SimulationConfig.h"

SimulationConfig::SimulationConfig()
    : mapWidth(10),
      mapHeight(10),
      initialPopulation(6),
      maxTicks(10),
      foodPrice(10),
      maxAge(90),
      maxPopulation(25),
      reproductionChancePercent(15),
      ticksPerYear(12) {}

SimulationConfig& SimulationConfig::getInstance() {
    static SimulationConfig instance;
    return instance;
}

int SimulationConfig::getMapWidth() const {
    return mapWidth;
}

int SimulationConfig::getMapHeight() const {
    return mapHeight;
}

int SimulationConfig::getInitialPopulation() const {
    return initialPopulation;
}

int SimulationConfig::getMaxTicks() const {
    return maxTicks;
}

int SimulationConfig::getFoodPrice() const {
    return foodPrice;
}

int SimulationConfig::getMaxAge() const {
    return maxAge;
}

int SimulationConfig::getMaxPopulation() const {
    return maxPopulation;
}

int SimulationConfig::getReproductionChancePercent() const {
    return reproductionChancePercent;
}

int SimulationConfig::getTicksPerYear() const {
    return ticksPerYear;
}