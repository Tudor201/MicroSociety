#include "World.h"
#include "SimulationConfig.h"
#include "RandomGenerator.h"

#include "../patterns/AgentFactory.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

World::World()
    : width(SimulationConfig::getInstance().getMapWidth()),
      height(SimulationConfig::getInstance().getMapHeight()),
      terrain(width, height, CellType::Empty),
      populationDensity(width, height, 0),
      nextAgentId(1) {}

void World::recalculatePopulationDensity() {
    populationDensity.fill(0);

    for (const auto& agent : agents) {
        Position position = agent->getPosition();

        if (agent->isAlive() && populationDensity.isInside(position.getX(), position.getY())) {
            populationDensity.at(position.getX(), position.getY())++;
        }
    }
}

void World::spawnInitialAgents() {
    int population = SimulationConfig::getInstance().getInitialPopulation();

    for (int i = 0; i < population; i++) {
        AgentType type;

        if (i % 3 == 0) {
            type = AgentType::Worker;
        } else if (i % 3 == 1) {
            type = AgentType::Trader;
        } else {
            type = AgentType::Student;
        }

        int id = nextAgentId++;
        std::unique_ptr<Agent> agent = AgentFactory::createAgent(type, id);

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

    recalculatePopulationDensity();
    std::cout << agents.size() << " agents spawned.\n";
}

void World::update() {
    std::cout << "World updating agents...\n";

    for (auto& agent : agents) {
        if (agent->isAlive()) {
            agent->update(*this);
        }
    }

    applyLivingCosts();
    removeDeadAgents();
    handleReproduction();
    recalculatePopulationDensity();
}

void World::display() const {
    std::cout << "\n--- World map ---\n";

    Grid<char> displayMap(width, height, '.');

    for (const auto& agent : agents) {
        Position position = agent->getPosition();

        if (agent->isAlive() && displayMap.isInside(position.getX(), position.getY())) {
            displayMap.at(position.getX(), position.getY()) = 'A';
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << displayMap.at(x, y) << ' ';
        }

        std::cout << '\n';
    }

    std::cout << "\n--- Agents ---\n";

    for (const auto& agent : agents) {
        agent->display();
    }

    std::cout << "--------------\n\n";
}

void World::clearAgents() {
    agents.clear();
    nextAgentId = 1;
    recalculatePopulationDensity();
}

void World::addAgent(std::unique_ptr<Agent> agent) {
    if (agent != nullptr) {
        if (agent->getId() >= nextAgentId) {
            nextAgentId = agent->getId() + 1;
        }

        agents.push_back(std::move(agent));
        recalculatePopulationDensity();
    }
}

bool World::isInside(const Position& position) const {
    return terrain.isInside(position.getX(), position.getY());
}

bool World::moveAgent(Agent& agent, int dx, int dy) {
    Position newPosition = agent.getPosition();

    newPosition.moveBy(dx, dy);

    if (!isInside(newPosition)) {
        return false;
    }

    agent.setPosition(newPosition);
    recalculatePopulationDensity();
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

const Grid<int>& World::getPopulationDensity() const {
    return populationDensity;
}

const std::vector<std::unique_ptr<Agent>>& World::getAgents() const {
    return agents;
}

void World::removeDeadAgents() {
    int maxAge = SimulationConfig::getInstance().getMaxAge();

    agents.erase(
        std::remove_if(
            agents.begin(),
            agents.end(),
            [maxAge](const std::unique_ptr<Agent>& agent) {
                bool shouldDie = !agent->isAlive() || agent->getAge() > maxAge;

                if (shouldDie) {
                    EventBus::getInstance().publish(
                        SimulationEvent(
                            EventType::AgentDied,
                            agent->getId(),
                            "Agent #" + std::to_string(agent->getId()) + " died."
                        )
                    );
                }

                return shouldDie;
            }
        ),
        agents.end()
    );
}

bool World::canReproduce(const Agent& agent) const {
    int adultAge = SimulationConfig::getInstance().getAdultAge();

    return agent.isAlive()
           && agent.getAge() >= adultAge
           && agent.getAge() <= 60
           && agent.getHealth() > 60
           && agent.getHappiness() > 70
           && agent.getEnergy() > 50
           && agent.getMoney() > 80;
}

std::unique_ptr<Agent> World::createChild(const Agent& parent1, const Agent& parent2) {
    (void)parent2;

    RandomGenerator& random = RandomGenerator::getInstance();

    int typeChoice = random.getInt(0, 2);
    AgentType childType;

    if (typeChoice == 0) {
        childType = AgentType::Worker;
    } else if (typeChoice == 1) {
        childType = AgentType::Trader;
    } else {
        childType = AgentType::Student;
    }

    int childId = nextAgentId++;
    std::unique_ptr<Agent> child = AgentFactory::createAgent(childType, childId);

    if (child != nullptr) {
        child->setPosition(parent1.getPosition());
        child->setAge(0);
        child->setTicksLived(0);

        child->changeMoney(20 - child->getMoney());
        child->changeHunger(20 - child->getHunger());
        child->changeEnergy(80 - child->getEnergy());
        child->changeHappiness(70 - child->getHappiness());
        child->changeHealth(100 - child->getHealth());
    }

    return child;
}

bool World::agentIsAlreadyParent(int id, const std::vector<int>& usedParentIds) const {
    return std::find(usedParentIds.begin(), usedParentIds.end(), id) != usedParentIds.end();
}

void World::handleReproduction() {
    SimulationConfig& config = SimulationConfig::getInstance();
    RandomGenerator& random = RandomGenerator::getInstance();

    if (getAgentCount() >= config.getMaxPopulation()) {
        return;
    }

    int birthsThisTick = 0;
    std::vector<int> usedParentIds;
    std::vector<std::unique_ptr<Agent>> newborns;

    for (size_t i = 0; i < agents.size(); i++) {
        if (birthsThisTick >= config.getMaxBirthsPerTick()) {
            break;
        }

        for (size_t j = i + 1; j < agents.size(); j++) {
            if (birthsThisTick >= config.getMaxBirthsPerTick()
                || getAgentCount() + static_cast<int>(newborns.size()) >= config.getMaxPopulation()) {
                break;
            }

            Agent& first = *agents[i];
            Agent& second = *agents[j];

            if (agentIsAlreadyParent(first.getId(), usedParentIds)
                || agentIsAlreadyParent(second.getId(), usedParentIds)) {
                continue;
            }

            Position p1 = first.getPosition();
            Position p2 = second.getPosition();
            int distance = std::abs(p1.getX() - p2.getX()) + std::abs(p1.getY() - p2.getY());

            if (distance > 1 || !canReproduce(first) || !canReproduce(second)) {
                continue;
            }

            if (random.getInt(1, 100) > config.getReproductionChancePercent()) {
                continue;
            }

            std::unique_ptr<Agent> child = createChild(first, second);

            if (child == nullptr) {
                continue;
            }

            int childId = child->getId();

            first.changeEnergy(-10);
            second.changeEnergy(-10);
            first.changeMoney(-10);
            second.changeMoney(-10);

            usedParentIds.push_back(first.getId());
            usedParentIds.push_back(second.getId());
            birthsThisTick++;

            EventBus::getInstance().publish(
                SimulationEvent(
                    EventType::AgentBorn,
                    childId,
                    "Agent #" + std::to_string(childId) + " was born."
                )
            );

            newborns.push_back(std::move(child));
        }
    }

    for (auto& newborn : newborns) {
        agents.push_back(std::move(newborn));
    }
}

void World::applyLivingCosts() {
    int livingCost = SimulationConfig::getInstance().getLivingCostPerTick();

    if (livingCost <= 0) {
        return;
    }

    for (auto& agent : agents) {
        if (!agent->isAlive()) {
            continue;
        }

        if (agent->getMoney() >= livingCost) {
            agent->changeMoney(-livingCost);
        } else {
            int currentMoney = agent->getMoney();

            if (currentMoney > 0) {
                agent->changeMoney(-currentMoney);
            }

            agent->changeHunger(4);
            agent->changeHappiness(-3);
            agent->changeHealth(-2);

            EventBus::getInstance().publish(
                SimulationEvent(
                    EventType::AgentFailedAction,
                    agent->getId(),
                    "Agent #" + std::to_string(agent->getId()) + " could not afford the living cost."
                )
            );
        }
    }
}