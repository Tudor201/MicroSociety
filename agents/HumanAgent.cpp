#include "HumanAgent.h"
#include "../ai/NeedsBasedStrategy.h"
#include "../actions/Action.h"
#include <iostream>
#include <memory>

HumanAgent::HumanAgent(int id, const std::string& name, const Position& position)
    : Agent(id, position, 30, 100, 100, 50),
      name(name),
      strategy(std::make_shared<NeedsBasedStrategy>()) {}

void HumanAgent::update(World& world) {
    if (strategy != nullptr) {
        std::unique_ptr<Action> action = strategy->chooseAction(*this, world);

        if (action != nullptr) {
            std::cout << name << " chose action: " << action->getName() << ".\n";
            action->execute(*this, world);
        }
    }
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