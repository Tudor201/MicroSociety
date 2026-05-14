#include "SaveManager.h"
#include "../core/World.h"
#include "../core/Position.h"
#include "../agents/Agent.h"
#include "../patterns/AgentFactory.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

bool SaveManager::saveWorld(const World& world, const std::string& filePath) const {
    std::filesystem::create_directories("data");

    std::ofstream fout(filePath);

    if (!fout.is_open()) {
        std::cout << "Could not open save file for writing.\n";
        return false;
    }

    fout << "MICROSOCIETY_SAVE\n";
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
             << agent->getAge() << '\n';
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

    if (header != "MICROSOCIETY_SAVE") {
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

        fin >> type >> id >> x >> y >> hunger >> energy >> money >> happiness >> health >> age;

        if (!fin) {
            std::cout << "Error while reading save file.\n";
            return false;
        }

        std::unique_ptr<Agent> agent = AgentFactory::createAgentFromTypeName(type, id);

        if (agent == nullptr) {
            std::cout << "Unknown agent type in save file: " << type << '\n';
            continue;
        }

        agent->setPosition(Position(x, y));

        agent->changeHunger(hunger - agent->getHunger());
        agent->changeEnergy(energy - agent->getEnergy());
        agent->changeMoney(money - agent->getMoney());
        agent->changeHappiness(happiness - agent->getHappiness());
        agent->changeHealth(health - agent->getHealth());
        agent->setAge(age);

        world.addAgent(std::move(agent));
    }

    return true;
}