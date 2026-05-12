#include "AgentFactory.h"
#include "../agents/WorkerAgent.h"
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
    }

    return nullptr;
}