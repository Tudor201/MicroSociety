#include "MoveAction.h"
#include "../agents/Agent.h"
#include "../core/World.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"

#include <iostream>

void MoveAction::execute(Agent& agent, World& world) {
    bool moved = world.moveAgent(agent, 1, 0);

    if (moved) {
        agent.changeHunger(3);
        agent.changeEnergy(-2);

        std::cout << "Agent #" << agent.getId() << " moved to position ("
                  << agent.getPosition().x << ", "
                  << agent.getPosition().y << ").\n";

        EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentMoved,
                agent.getId(),
                "Agent #" + std::to_string(agent.getId()) + " moved to a new position."
            )
        );
    } else {
        agent.changeHappiness(-1);

        std::cout << "Agent #" << agent.getId()
                  << " tried to move, but reached the edge of the world.\n";

        EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentFailedAction,
                agent.getId(),
                "Agent #" + std::to_string(agent.getId()) + " tried to move outside the world."
            )
        );
    }
}

std::string MoveAction::getName() const {
    return "Move";
}