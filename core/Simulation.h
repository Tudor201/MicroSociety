#ifndef MICROSOCIETY_SIMULATION_H
#define MICROSOCIETY_SIMULATION_H

#include "World.h"
#include "../systems/StatisticsManager.h"
#include "../systems/EventLogger.h"
#include "../systems/SaveManager.h"

#include <string>

class Simulation {
private:
    World world;
    StatisticsManager statisticsManager;
    EventLogger eventLogger;
    SaveManager saveManager;
    bool running;
    int currentTick;

    int readInt(const std::string& message) const;
    int generateNextAgentId() const;

    void displayMenu() const;
    void runTicks();
    void spawnAgentManual();
    void showAllAgents() const;
    void saveLoadMenu();
    void showEditConfigMenu();

public:
    Simulation();

    void run();
    void update();
    void display() const;
};

#endif //MICROSOCIETY_SIMULATION_H