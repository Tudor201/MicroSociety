#include "HumanAgent.h"
#include "../ai/NeedsBasedStrategy.h"

#include "../actions/Action.h"

#include "../patterns/EventBus.h"
#include "../patterns/Event.h"

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
            EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentChoseAction,
                getId(),
                name + " chose action: " + action->getName() + "."
                )
            );
            action->execute(*this, world);
        }
    }

    updateLifeStatus();
}

void HumanAgent::display() const {
    std::cout << "HumanAgent #" << id
              << " | Name: " << name
              << " | Position: (" << position.getX() << ", " << position.getY() << ")"
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