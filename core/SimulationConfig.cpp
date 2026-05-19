#include "SimulationConfig.h"

#include <fstream>
#include <string>

SimulationConfig::SimulationConfig()
    : mapWidth(10),
      mapHeight(10),
      initialPopulation(6),
      maxTicks(10),
      foodPrice(10),
      maxAge(90),
      maxPopulation(25),
      reproductionChancePercent(15),
      ticksPerYear(12),
      adultAge(18),
      maxBirthsPerTick(2),
      livingCostPerTick(2) {

    std::ifstream fin("data/config.txt");

    if (!fin.is_open()) {
        fin.open("../data/config.txt");
    }

    if (!fin.is_open()) {
        return;
    }

    std::string key;
    int value;

    while (fin >> key >> value) {
        if (key == "mapWidth") {
            mapWidth = value;
        } else if (key == "mapHeight") {
            mapHeight = value;
        } else if (key == "initialPopulation") {
            initialPopulation = value;
        } else if (key == "maxTicks") {
            maxTicks = value;
        } else if (key == "foodPrice") {
            foodPrice = value;
        } else if (key == "maxAge") {
            maxAge = value;
        } else if (key == "maxPopulation") {
            maxPopulation = value;
        } else if (key == "reproductionChancePercent") {
            reproductionChancePercent = value;
        } else if (key == "ticksPerYear") {
            ticksPerYear = value;
        } else if (key == "adultAge") {
            adultAge = value;
        } else if (key == "maxBirthsPerTick") {
            maxBirthsPerTick = value;
        } else if (key == "livingCostPerTick") {
            livingCostPerTick = value;
        }
    }
}

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

int SimulationConfig::getAdultAge() const {
    return adultAge;
}

int SimulationConfig::getMaxBirthsPerTick() const {
    return maxBirthsPerTick;
}

int SimulationConfig::getLivingCostPerTick() const {
    return livingCostPerTick;
}