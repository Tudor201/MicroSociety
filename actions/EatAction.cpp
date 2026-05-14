#include "EatAction.h"
#include "../agents/Agent.h"
#include "../core/SimulationConfig.h"
#include <iostream>

void EatAction::execute(Agent& agent, World& world) {
    (void)world;

    const int foodPrice = SimulationConfig::getInstance().getFoodPrice();

    if (agent.getMoney() >= foodPrice) {
        agent.changeMoney(-foodPrice);
        agent.changeHunger(-35);
        agent.changeEnergy(5);
        agent.changeHappiness(3);

        std::cout << "Agent #" << agent.getId() << " ate food.\n";
    } else {
        std::cout << "Agent #" << agent.getId() << " wanted to eat but did not have enough money.\n";
        agent.changeHappiness(-5);
    }
}

std::string EatAction::getName() const {
    return "Eat";
}