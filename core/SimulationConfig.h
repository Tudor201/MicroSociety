#ifndef MICROSOCIETY_SIMULATIONCONFIG_H
#define MICROSOCIETY_SIMULATIONCONFIG_H

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
};

#endif //MICROSOCIETY_SIMULATIONCONFIG_H