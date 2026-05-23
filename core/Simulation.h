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

    void clearScreen() const;
    void waitForEnter() const;
    void printHeader() const;

    void displayMainMenu() const;
    void displayPlayMenu() const;
    void displayInspectMenu() const;
    void displayManageMenu() const;

    void playMenu();
    void inspectMenu() const;
    void manageMenu();

    void runTicks();
    void runTicks(int ticks);

    void spawnAgentManual();
    void showAllAgents() const;
    void saveLoadMenu();
    void showEditConfigMenu();
    void showAfterTickReport(int ticksRun) const;

public:
    Simulation();

    void run();
    void update();
    void display() const;
};

#endif //MICROSOCIETY_SIMULATION_H