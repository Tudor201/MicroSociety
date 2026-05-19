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
      livingCostPerTick(2),
      maxStoredEvents(20) {

    std::ifstream fin("data/config.txt");

    if (!fin.is_open()) {
        fin.clear();
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
        } else if (key == "maxStoredEvents") {
            maxStoredEvents = value;
        }
    }
}

SimulationConfig& SimulationConfig::getInstance() {
    static SimulationConfig instance;
    return instance;
}

bool SimulationConfig::setValue(const std::string& key, int value) {
    if (key == "mapWidth") {
        if (value <= 0) return false;
        mapWidth = value;
    } else if (key == "mapHeight") {
        if (value <= 0) return false;
        mapHeight = value;
    } else if (key == "initialPopulation") {
        if (value < 0) return false;
        initialPopulation = value;
    } else if (key == "maxTicks") {
        if (value <= 0) return false;
        maxTicks = value;
    } else if (key == "foodPrice") {
        if (value < 0) return false;
        foodPrice = value;
    } else if (key == "maxAge") {
        if (value <= 0) return false;
        maxAge = value;
    } else if (key == "maxPopulation") {
        if (value <= 0) return false;
        maxPopulation = value;
    } else if (key == "reproductionChancePercent") {
        if (value < 0 || value > 100) return false;
        reproductionChancePercent = value;
    } else if (key == "ticksPerYear") {
        if (value <= 0) return false;
        ticksPerYear = value;
    } else if (key == "adultAge") {
        if (value < 0) return false;
        adultAge = value;
    } else if (key == "maxBirthsPerTick") {
        if (value < 0) return false;
        maxBirthsPerTick = value;
    } else if (key == "livingCostPerTick") {
        if (value < 0) return false;
        livingCostPerTick = value;
    } else if (key == "maxStoredEvents") {
        if (value <= 0) return false;
        maxStoredEvents = value;
    } else {
        return false;
    }

    return true;
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

int SimulationConfig::getMaxStoredEvents() const {
    return maxStoredEvents;
}