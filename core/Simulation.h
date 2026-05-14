#ifndef MICROSOCIETY_SIMULATION_H
#define MICROSOCIETY_SIMULATION_H
#include "World.h"
#include "../systems/StatisticsManager.h"

class Simulation {
private:
    World world;
    StatisticsManager statisticsManager;
    bool running;
    int currentTick;

public:
    Simulation();

    void run();
    void update();
    void display() const;
};

#endif //MICROSOCIETY_SIMULATION_H