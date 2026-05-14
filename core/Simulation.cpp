#include "Simulation.h"
#include "SimulationConfig.h"
#include <iostream>

Simulation::Simulation()
    : running(false), currentTick(0) {world.spawnInitialAgents();}

void Simulation::run() {
    running = true;

    std::cout << "MicroSociety simulation started.\n";

    int maxTicks = SimulationConfig::getInstance().getMaxTicks();

    while (running && currentTick < maxTicks) {
        update();
        display();
        currentTick++;
    }

    std::cout << "Simulation ended.\n";
}

void Simulation::update() {
    std::cout << "Simulation tick " << currentTick + 1 << "\n";
    world.update();
}

void Simulation::display() const {
    world.display();
}