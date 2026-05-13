#include "World.h"
#include "../patterns/AgentFactory.h"

#include <iostream>
#include <utility>

World::World() {
    std::cout << "World created.\n";
}

void World::spawnInitialAgents() {
    for (int i = 1; i <= 6; i++) {
        AgentType type;

        if (i % 3 == 1) {
            type = AgentType::Worker;
        } else if (i % 3 == 2) {
            type = AgentType::Trader;
        } else {
            type = AgentType::Student;
        }

        std::unique_ptr<Agent> agent = AgentFactory::createAgent(type, i);

        if (agent != nullptr) {
            agents.push_back(std::move(agent));
        }
    }

    std::cout << agents.size() << " agents spawned.\n";
}

void World::update() {
    std::cout << "World updating agents...\n";

    for (auto& agent : agents) {
        agent->update(*this);
    }
}

void World::display() const {
    std::cout << "\n--- World state ---\n";

    for (const auto& agent : agents) {
        agent->display();
    }

    std::cout << "-------------------\n\n";
}

int World::getAgentCount() const {
    return static_cast<int>(agents.size());
}