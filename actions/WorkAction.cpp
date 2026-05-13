#include "WorkAction.h"
#include "../agents/Agent.h"
#include "../agents/WorkerAgent.h"
#include "../agents/TraderAgent.h"
#include "../agents/StudentAgent.h"

#include <iostream>

void WorkAction::execute(Agent& agent, World& world) {
    (void)world;

    if (auto worker = dynamic_cast<WorkerAgent*>(&agent)) {
        worker->earnMoney();

        agent.changeHunger(7);
        agent.changeEnergy(-10);
        agent.changeHappiness(1);

        std::cout << "Agent #" << agent.getId() << " worked and earned money.\n";
        return;
    }

    if (auto trader = dynamic_cast<TraderAgent*>(&agent)) {
        trader->makeTrade();

        agent.changeHunger(5);
        agent.changeEnergy(-8);
        agent.changeHappiness(2);

        std::cout << "Agent #" << agent.getId() << " made a trade.\n";
        return;
    }

    if (auto student = dynamic_cast<StudentAgent*>(&agent)) {
        student->study();

        agent.changeHunger(4);
        agent.changeEnergy(-7);
        agent.changeMoney(-2);

        std::cout << "Agent #" << agent.getId() << " studied.\n";
        return;
    }

    std::cout << "Agent #" << agent.getId() << " cannot perform this action.\n";
}

std::string WorkAction::getName() const {
    return "Work";
}