#include "Simulation.h"
#include <iostream>

Simulation::Simulation()
    : running(false), currentTick(0) {world.spawnInitialAgents();}

void Simulation::run() {
    running = true;

    std::cout << "MicroSociety simulation started.\n";

    while (running && currentTick < 3) {
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