#include "MoveAction.h"
#include "../agents/Agent.h"
#include <iostream>

void MoveAction::execute(Agent& agent, World& world) {
    (void)world;

    agent.moveBy(1, 0);
    agent.changeHunger(3);
    agent.changeEnergy(-2);

    std::cout << "Agent #" << agent.getId() << " moved to position ("
              << agent.getPosition().x << ", "
              << agent.getPosition().y << ").\n";
}

std::string MoveAction::getName() const {
    return "Move";
}