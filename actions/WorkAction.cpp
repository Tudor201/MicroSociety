#include "WorkAction.h"
#include "../agents/Agent.h"
#include "../agents/WorkerAgent.h"
#include <iostream>

void WorkAction::execute(Agent& agent, World& world) {
    (void)world;

    WorkerAgent* worker = dynamic_cast<WorkerAgent*>(&agent);

    if (worker != nullptr) {
        worker->earnMoney();

        agent.changeHunger(7);
        agent.changeEnergy(-10);
        agent.changeHappiness(1);

        std::cout << "Agent #" << agent.getId() << " worked and earned money.\n";
    } else {
        std::cout << "Agent #" << agent.getId() << " cannot work.\n";
    }
}

std::string WorkAction::getName() const {
    return "Work";
}