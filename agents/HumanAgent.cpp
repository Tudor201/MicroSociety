#include "HumanAgent.h"
#include "../ai/NeedsBasedStrategy.h"
#include "../actions/Action.h"
#include <iostream>
#include <memory>

HumanAgent::HumanAgent(int id, const std::string& name, const Position& position)
    : Agent(id, position, 30, 100, 100, 50),
      name(name),
      strategy(std::make_shared<NeedsBasedStrategy>()),
      strategyObserver(strategy) {}

void HumanAgent::update(World& world) {
    std::shared_ptr<DecisionStrategy> observedStrategy = strategyObserver.lock();

    if (observedStrategy != nullptr) {
        std::unique_ptr<Action> action = observedStrategy->chooseAction(*this, world);

        if (action != nullptr) {
            std::cout << name << " chose action: " << action->getName() << ".\n";
            action->execute(*this, world);
        }
    }

    updateLifeStatus();
}

void HumanAgent::display() const {
    std::cout << "HumanAgent #" << id
              << " | Name: " << name
              << " | Position: (" << position.x << ", " << position.y << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << " | Health: " << health
              << " | Age: " << age
              << '\n';
}

const std::string& HumanAgent::getName() const {
    return name;
}