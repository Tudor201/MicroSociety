#include "AgentFactory.h"
#include "../agents/WorkerAgent.h"
#include "../agents/TraderAgent.h"
#include "../agents/StudentAgent.h"
#include "../core/Position.h"

#include <memory>
#include <string>

std::unique_ptr<Agent> AgentFactory::createAgent(AgentType type, int id) {
    switch (type) {
        case AgentType::Worker:
            return std::make_unique<WorkerAgent>(
                id,
                "Worker_" + std::to_string(id),
                Position(id, id),
                25,
                "Builder"
            );

        case AgentType::Trader:
            return std::make_unique<TraderAgent>(
                id,
                "Trader_" + std::to_string(id),
                Position(id, id),
                40
            );

        case AgentType::Student:
            return std::make_unique<StudentAgent>(
                id,
                "Student_" + std::to_string(id),
                Position(id, id),
                "University of Bucharest"
            );
    }

    return nullptr;
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