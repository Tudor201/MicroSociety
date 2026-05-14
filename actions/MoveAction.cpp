#include "MoveAction.h"
#include "../agents/Agent.h"
#include "../core/World.h"

#include <iostream>

void MoveAction::execute(Agent& agent, World& world) {
    bool moved = world.moveAgent(agent, 1, 0);

    if (moved) {
        agent.changeHunger(3);
        agent.changeEnergy(-2);

        std::cout << "Agent #" << agent.getId() << " moved to position ("
                  << agent.getPosition().x << ", "
                  << agent.getPosition().y << ").\n";
    } else {
        agent.changeHappiness(-1);

        std::cout << "Agent #" << agent.getId()
                  << " tried to move, but reached the edge of the world.\n";
    }
}

std::string MoveAction::getName() const {
    return "Move";
}