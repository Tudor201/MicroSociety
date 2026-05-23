#include "MoveAction.h"
#include "../agents/Agent.h"
#include "../core/World.h"
#include "../core/RandomGenerator.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"

#include <string>

void MoveAction::execute(Agent& agent, World& world) {
    RandomGenerator& random = RandomGenerator::getInstance();

    int direction = random.getInt(0, 3);

    int dx = 0;
    int dy = 0;

    switch (direction) {
        case 0:
            dx = 1;
            break;
        case 1:
            dx = -1;
            break;
        case 2:
            dy = 1;
            break;
        case 3:
            dy = -1;
            break;
        default:
            break;
    }

    bool moved = world.moveAgent(agent, dx, dy);

    if (moved) {
        agent.changeHunger(3);
        agent.changeEnergy(-2);

        EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentMoved,
                agent.getId(),
                "Agent #" + std::to_string(agent.getId()) + " moved to a new position."
            )
        );
    } else {
        agent.changeHappiness(-1);

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