#include "SaveManager.h"

#include "../core/World.h"
#include "../core/Position.h"

#include "../agents/Agent.h"
#include "../agents/WorkerAgent.h"
#include "../agents/TraderAgent.h"
#include "../agents/StudentAgent.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

namespace {
    void restoreCommonState(
        Agent& agent,
        int x,
        int y,
        int hunger,
        int energy,
        int money,
        int happiness,
        int health,
        int age,
        int ticksLived
    ) {
        agent.setPosition(Position(x, y));

        agent.changeHunger(hunger - agent.getHunger());
        agent.changeEnergy(energy - agent.getEnergy());
        agent.changeMoney(money - agent.getMoney());
        agent.changeHappiness(happiness - agent.getHappiness());
        agent.changeHealth(health - agent.getHealth());

        agent.setAge(age);
        agent.setTicksLived(ticksLived);
    }
}

bool SaveManager::saveWorld(const World& world, const std::string& filePath) const {
    std::filesystem::create_directories("data");

    std::ofstream fout(filePath);

    if (!fout.is_open()) {
        std::cout << "Could not open save file for writing.\n";
        return false;
    }

    fout << "MICROSOCIETY_SAVE_V3\n";
    fout << world.getAgentCount() << '\n';

    const auto& agents = world.getAgents();

    for (const auto& agent : agents) {
        Position position = agent->getPosition();

        fout << agent->getType() << ' '
             << agent->getId() << ' '
             << position.x << ' '
             << position.y << ' '
             << agent->getHunger() << ' '
             << agent->getEnergy() << ' '
             << agent->getMoney() << ' '
             << agent->getHappiness() << ' '
             << agent->getHealth() << ' '
             << agent->getAge() << ' '
             << agent->getTicksLived() << ' ';

        if (const auto* worker = dynamic_cast<const WorkerAgent*>(agent.get())) {
            fout << worker->getSalary() << ' '
                 << std::quoted(worker->getJobName()) << '\n';
        } else if (const auto* trader = dynamic_cast<const TraderAgent*>(agent.get())) {
            fout << trader->getProfitPerTrade() << '\n';
        } else if (const auto* student = dynamic_cast<const StudentAgent*>(agent.get())) {
            fout << std::quoted(student->getUniversity()) << ' '
                 << student->getKnowledgeLevel() << '\n';
        } else {
            fout << '\n';
        }
    }

    return true;
}

bool SaveManager::loadWorld(World& world, const std::string& filePath) const {
    std::ifstream fin(filePath);

    if (!fin.is_open()) {
        return false;
    }

    std::string header;
    std::getline(fin, header);

    if (header != "MICROSOCIETY_SAVE_V3") {
        std::cout << "Invalid save file format.\n";
        return false;
    }

    int agentCount;
    fin >> agentCount;

    if (agentCount < 0) {
        std::cout << "Invalid agent count in save file.\n";
        return false;
    }

    world.clearAgents();

    for (int i = 0; i < agentCount; i++) {
        std::string type;
        int id;
        int x;
        int y;
        int hunger;
        int energy;
        int money;
        int happiness;
        int health;
        int age;
        int ticksLived;

        fin >> type
            >> id
            >> x
            >> y
            >> hunger
            >> energy
            >> money
            >> happiness
            >> health
            >> age
            >> ticksLived;

        if (!fin) {
            std::cout << "Error while reading common agent data.\n";
            return false;
        }

        std::unique_ptr<Agent> agent;

        if (type == "Worker") {
            int salary;
            std::string jobName;

            fin >> salary >> std::quoted(jobName);

            if (!fin) {
                std::cout << "Error while reading Worker data.\n";
                return false;
            }

            agent = std::make_unique<WorkerAgent>(
                id,
                "Worker_" + std::to_string(id),
                Position(x, y),
                salary,
                jobName
            );
        } else if (type == "Trader") {
            int profitPerTrade;

            fin >> profitPerTrade;

            if (!fin) {
                std::cout << "Error while reading Trader data.\n";
                return false;
            }

            agent = std::make_unique<TraderAgent>(
                id,
                "Trader_" + std::to_string(id),
                Position(x, y),
                profitPerTrade
            );
        } else if (type == "Student") {
            std::string university;
            int knowledgeLevel;

            fin >> std::quoted(university) >> knowledgeLevel;

            if (!fin) {
                std::cout << "Error while reading Student data.\n";
                return false;
            }

            auto student = std::make_unique<StudentAgent>(
                id,
                "Student_" + std::to_string(id),
                Position(x, y),
                university
            );

            student->setKnowledgeLevel(knowledgeLevel);

            agent = std::move(student);
        } else {
            std::cout << "Unknown agent type in save file: " << type << '\n';
            return false;
        }

        restoreCommonState(
            *agent,
            x,
            y,
            hunger,
            energy,
            money,
            happiness,
            health,
            age,
            ticksLived
        );

        world.addAgent(std::move(agent));
    }

    return true;
}