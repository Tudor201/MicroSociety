#include "AgentFactory.h"
#include "../agents/Agent.h"
#include "../agents/WorkerAgent.h"
#include "../agents/TraderAgent.h"
#include "../agents/StudentAgent.h"

#include "../core/Position.h"
#include "../core/SimulationConfig.h"
#include "../core/RandomGenerator.h"

#include <memory>
#include <string>

std::unique_ptr<Agent> AgentFactory::createAgent(AgentType type, int id) {
    RandomGenerator& random = RandomGenerator::getInstance();
    SimulationConfig& config = SimulationConfig::getInstance();

    int x = random.getInt(0, config.getMapWidth() - 1);
    int y = random.getInt(0, config.getMapHeight() - 1);

    Position position(x, y);

    std::unique_ptr<Agent> agent;

    switch (type) {
        case AgentType::Worker:
            agent = std::make_unique<WorkerAgent>(
                id,
                "Worker_" + std::to_string(id),
                position,
                random.getInt(20, 45),
                "Builder"
            );
            break;

        case AgentType::Trader:
            agent = std::make_unique<TraderAgent>(
                id,
                "Trader_" + std::to_string(id),
                position,
                random.getInt(25, 60)
            );
            break;

        case AgentType::Student:
            agent = std::make_unique<StudentAgent>(
                id,
                "Student_" + std::to_string(id),
                position,
                "University of Bucharest"
            );
            break;
    }

    if (agent != nullptr) {
        int randomHunger = random.getInt(10, 80);
        int randomEnergy = random.getInt(40, 100);
        int randomMoney = random.getInt(50, 200);
        int randomHappiness = random.getInt(30, 90);

        agent->changeHunger(randomHunger - agent->getHunger());
        agent->changeEnergy(randomEnergy - agent->getEnergy());
        agent->changeMoney(randomMoney - agent->getMoney());
        agent->changeHappiness(randomHappiness - agent->getHappiness());
    }

    return agent;
}

std::unique_ptr<Agent> AgentFactory::createAgentFromTypeName(const std::string& typeName, int id) {
    if (typeName == "Worker") {
        return createAgent(AgentType::Worker, id);
    }

    if (typeName == "Trader") {
        return createAgent(AgentType::Trader, id);
    }

    if (typeName == "Student") {
        return createAgent(AgentType::Student, id);
    }

    return nullptr;
}