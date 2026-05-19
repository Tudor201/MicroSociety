#include "StatisticsManager.h"
#include "../core/World.h"
#include "../agents/Agent.h"
#include "../utils/TemplateUtils.h"

#include <iostream>
#include <iomanip>

void StatisticsManager::displayStatistics(const World& world) const {
    const auto& agents = world.getAgents();

    if (agents.empty()) {
        std::cout << "\n--- Statistics ---\n";
        std::cout << "No agents in the world.\n";
        std::cout << "------------------\n\n";
        return;
    }

    double totalHunger = 0;
    double totalEnergy = 0;
    double totalMoney = 0;
    double totalHappiness = 0;
    double totalHealth = 0;
    double totalAge = 0;

    int aliveCount = countMatching(
        agents,
        [](const std::unique_ptr<Agent>& agent) {
            return agent->isAlive();
        }
    );

    for (const auto& agent : agents) {
        totalHunger += agent->getHunger();
        totalEnergy += agent->getEnergy();
        totalMoney += agent->getMoney();
        totalHappiness += agent->getHappiness();
        totalHealth += agent->getHealth();
        totalAge += agent->getAge();
    }

    double agentCount = static_cast<double>(agents.size());

    std::vector<int> densityValues = world.getPopulationDensity().flatten();
    int maxAgentsInCell = findMax(densityValues);

    std::cout << "\n--- Statistics ---\n";
    std::cout << "Population: " << agents.size() << '\n';
    std::cout << "Alive agents: " << aliveCount << '\n';
    std::cout << "Max agents in one cell: " << maxAgentsInCell << '\n';

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Average hunger: " << totalHunger / agentCount << '\n';
    std::cout << "Average energy: " << totalEnergy / agentCount << '\n';
    std::cout << "Average money: " << totalMoney / agentCount << '\n';
    std::cout << "Average happiness: " << totalHappiness / agentCount << '\n';
    std::cout << "Average health: " << totalHealth / agentCount << '\n';
    std::cout << "Average age: " << totalAge / agentCount << '\n';

    std::cout << "------------------\n\n";
}