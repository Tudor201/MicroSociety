#include "Simulation.h"
#include "SimulationConfig.h"
#include <iostream>

Simulation::Simulation()
    : running(false), currentTick(0) {
    if (saveManager.loadWorld(world, "data/save.txt")) {
        std::cout << "World loaded from save file.\n";
    } else {
        world.spawnInitialAgents();
    }
}

void Simulation::run() {
    running = true;

    std::cout << "MicroSociety simulation started.\n";

    int maxTicks = SimulationConfig::getInstance().getMaxTicks();

    while (running && currentTick < maxTicks) {
        update();
        display();
        currentTick++;
    }

    if (saveManager.saveWorld(world, "data/save.txt")) {
        std::cout << "World saved successfully.\n";
    }

    std::cout << "Simulation ended.\n";
}

void Simulation::update() {
    std::cout << "Simulation tick " << currentTick + 1 << "\n";
    world.update();
}

void Simulation::display() const {
    world.display();
    statisticsManager.displayStatistics(world);
    eventLogger.displayRecentEvents();
}