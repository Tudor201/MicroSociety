#include "World.h"
#include "SimulationConfig.h"
#include "../patterns/AgentFactory.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"

#include <iostream>
#include <utility>
#include <string>

World::World()
    : width(SimulationConfig::getInstance().getMapWidth()),
      height(SimulationConfig::getInstance().getMapHeight()),
      terrain(width, height, CellType::Empty) {
    std::cout << "World created with size "
              << width << " x " << height << ".\n";
}

void World::spawnInitialAgents() {
    int population = SimulationConfig::getInstance().getInitialPopulation();

    for (int i = 1; i <= population; i++) {
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
            int spawnedId = agent->getId();

            EventBus::getInstance().publish(
                SimulationEvent(
                    EventType::AgentSpawned,
                    spawnedId,
                    "Agent #" + std::to_string(spawnedId) + " spawned in the world."
                )
            );

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
    std::cout << "\n--- World map ---\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool hasAgent = false;

            for (const auto& agent : agents) {
                Position position = agent->getPosition();

                if (position.x == x && position.y == y) {
                    hasAgent = true;
                    break;
                }
            }

            if (hasAgent) {
                std::cout << "A ";
            } else {
                std::cout << ". ";
            }
        }

        std::cout << '\n';
    }

    std::cout << "\n--- Agents ---\n";

    for (const auto& agent : agents) {
        agent->display();
    }

    std::cout << "--------------\n\n";
}

bool World::isInside(const Position& position) const {
    return terrain.isInside(position.x, position.y);
}

bool World::moveAgent(Agent& agent, int dx, int dy) {
    Position newPosition = agent.getPosition();

    newPosition.x += dx;
    newPosition.y += dy;

    if (!isInside(newPosition)) {
        return false;
    }

    agent.setPosition(newPosition);
    return true;
}

int World::getAgentCount() const {
    return static_cast<int>(agents.size());
}

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}

const std::vector<std::unique_ptr<Agent>>& World::getAgents() const {
    return agents;
}