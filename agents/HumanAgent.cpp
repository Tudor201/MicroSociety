#include "HumanAgent.h"
#include <iostream>

HumanAgent::HumanAgent(int id, const std::string& name, const Position& position)
    : Agent(id, position, 30, 100, 100, 50),
      name(name) {}

void HumanAgent::update(World& world) {
    (void)world;

    changeHunger(5);
    changeEnergy(-3);
    changeHappiness(-1);
    moveBy(1, 0);

    std::cout << name << " is living normally.\n";
}

void HumanAgent::display() const {
    std::cout << "HumanAgent #" << id
              << " | Name: " << name
              << " | Position: (" << position.x << ", " << position.y << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << '\n';
}

const std::string& HumanAgent::getName() const {
    return name;
}