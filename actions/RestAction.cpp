#include "RestAction.h"
#include "../agents/Agent.h"
#include <iostream>

void RestAction::execute(Agent& agent, World& world) {
    (void)world;

    agent.changeEnergy(30);
    agent.changeHunger(2);
    agent.changeHappiness(1);

    std::cout << "Agent #" << agent.getId() << " rested.\n";
}

std::string RestAction::getName() const {
    return "Rest";
}