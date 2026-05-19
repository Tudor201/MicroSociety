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
      nextAgentId(1),
      terrain(width, height, CellType::Empty) {
    std::cout << "World created with size "
              << width << " x " << height << ".\n";
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

void World::clearAgents() {
    agents.clear();
    nextAgentId = 1;
}

void World::addAgent(std::unique_ptr<Agent> agent) {
    if (agent != nullptr) {
        if (agent->getId() >= nextAgentId) {
            nextAgentId = agent->getId() + 1;
        }

        agents.push_back(std::move(agent));
    }
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

void World::handleReproduction() {
    SimulationConfig& config = SimulationConfig::getInstance();
    RandomGenerator& random = RandomGenerator::getInstance();

    if (getAgentCount() >= config.getMaxPopulation()) {
        return;
    }

    int adultAge = config.getAdultAge();
    int maxBirthsPerTick = config.getMaxBirthsPerTick();
    int birthsThisTick = 0;

    std::vector<int> usedParentIds;
    std::vector<std::unique_ptr<Agent>> newborns;

    for (size_t i = 0; i < agents.size(); i++) {
        if (birthsThisTick >= maxBirthsPerTick) {
            break;
        }

        for (size_t j = i + 1; j < agents.size(); j++) {
            if (birthsThisTick >= maxBirthsPerTick) {
                break;
            }

            if (getAgentCount() + static_cast<int>(newborns.size()) >= config.getMaxPopulation()) {
                break;
            }

            Agent& first = *agents[i];
            Agent& second = *agents[j];

            bool firstAlreadyUsed =
                std::find(usedParentIds.begin(), usedParentIds.end(), first.getId()) != usedParentIds.end();

            bool secondAlreadyUsed =
                std::find(usedParentIds.begin(), usedParentIds.end(), second.getId()) != usedParentIds.end();

            if (firstAlreadyUsed || secondAlreadyUsed) {
                continue;
            }

            if (!first.isAlive() || !second.isAlive()) {
                continue;
            }

            Position p1 = first.getPosition();
            Position p2 = second.getPosition();

            int distance = std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);

            bool closeEnough = distance <= 1;

            bool firstCanReproduce =
                first.getAge() >= adultAge &&
                first.getAge() <= 60 &&
                first.getHealth() > 60 &&
                first.getHappiness() > 70 &&
                first.getEnergy() > 50 &&
                first.getMoney() > 80;

            bool secondCanReproduce =
                second.getAge() >= adultAge &&
                second.getAge() <= 60 &&
                second.getHealth() > 60 &&
                second.getHappiness() > 70 &&
                second.getEnergy() > 50 &&
                second.getMoney() > 80;

            if (!closeEnough || !firstCanReproduce || !secondCanReproduce) {
                continue;
            }

            int chance = random.getInt(1, 100);

            if (chance > config.getReproductionChancePercent()) {
                continue;
            }

            AgentType childType;

            int typeChoice = random.getInt(0, 2);

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
                child->setPosition(p1);
                child->setAge(0);
                child->setTicksLived(0);

                child->changeMoney(20 - child->getMoney());
                child->changeHunger(20 - child->getHunger());
                child->changeEnergy(80 - child->getEnergy());
                child->changeHappiness(70 - child->getHappiness());
                child->changeHealth(100 - child->getHealth());

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