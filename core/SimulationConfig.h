#ifndef MICROSOCIETY_SIMULATIONCONFIG_H
#define MICROSOCIETY_SIMULATIONCONFIG_H
#include <string>
class SimulationConfig {
private:
    int mapWidth;
    int mapHeight;
    int initialPopulation;

    int maxTicks;
    int foodPrice;
    int maxAge;
    int maxPopulation;

    int reproductionChancePercent;
    int ticksPerYear;
    int adultAge;

    int maxBirthsPerTick;
    int livingCostPerTick;
    int maxStoredEvents;

    SimulationConfig();

public:
    SimulationConfig(const SimulationConfig& other) = delete;
    SimulationConfig& operator=(const SimulationConfig& other) = delete;

    static SimulationConfig& getInstance();

    int getMapWidth() const;
    int getMapHeight() const;
    int getInitialPopulation() const;

    int getMaxTicks() const;
    int getFoodPrice() const;
    int getMaxAge() const;
    int getMaxPopulation() const;

    int getReproductionChancePercent() const;
    int getTicksPerYear() const;
    int getAdultAge() const;

    int getMaxBirthsPerTick() const;
    int getLivingCostPerTick() const;
    int getMaxStoredEvents() const;

    bool setValue(const std::string& key, int value);
};

#endif //MICROSOCIETY_SIMULATIONCONFIG_H