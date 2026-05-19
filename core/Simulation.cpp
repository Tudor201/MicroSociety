#include "Simulation.h"
#include "SimulationConfig.h"
#include "../patterns/AgentFactory.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

Simulation::Simulation()
    : running(false), currentTick(0) {
    if (saveManager.loadWorld(world, "data/save.txt")) {
        std::cout << "World loaded from save file.\n";
    } else {
        world.spawnInitialAgents();
    }
}

int Simulation::readInt(const std::string& message) const {
    int value;

    while (true) {
        std::cout << message;

        if (std::cin >> value) {
            return value;
        }

        std::cout << "Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int Simulation::generateNextAgentId() const {
    int maxId = 0;

    for (const auto& agent : world.getAgents()) {
        if (agent->getId() > maxId) {
            maxId = agent->getId();
        }
    }

    return maxId + 1;
}

void Simulation::displayMenu() const {
    std::cout << "\n=== MicroSociety Menu ===\n";
    std::cout << "1. Run simulation (N ticks)\n";
    std::cout << "2. Spawn agent manual\n";
    std::cout << "3. Show all agents\n";
    std::cout << "4. Show statistics\n";
    std::cout << "5. Show recent events\n";
    std::cout << "6. Save / Load\n";
    std::cout << "7. Show / edit config\n";
    std::cout << "0. Exit\n";
}

void Simulation::run() {
    running = true;
    std::cout << "MicroSociety simulation started.\n";

    while (running) {
        displayMenu();

        int option = readInt("Choose option: ");

        switch (option) {
            case 1:
                runTicks();
                break;
            case 2:
                spawnAgentManual();
                break;
            case 3:
                showAllAgents();
                break;
            case 4:
                statisticsManager.displayStatistics(world);
                break;
            case 5:
                eventLogger.displayRecentEvents(10);
                break;
            case 6:
                saveLoadMenu();
                break;
            case 7:
                showEditConfigMenu();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Invalid option.\n";
                break;
        }
    }

    std::cout << "Simulation ended.\n";
}

void Simulation::runTicks() {
    int ticks = readInt("How many ticks? ");

    if (ticks <= 0) {
        std::cout << "Number of ticks must be positive.\n";
        return;
    }

    int maxTicks = SimulationConfig::getInstance().getMaxTicks();

    for (int i = 0; i < ticks && currentTick < maxTicks; i++) {
        update();
        display();
        currentTick++;
    }

    if (currentTick >= maxTicks) {
        std::cout << "Max ticks reached.\n";
    }
}

void Simulation::spawnAgentManual() {
    if (world.getAgentCount() >= SimulationConfig::getInstance().getMaxPopulation()) {
        std::cout << "Max population reached.\n";
        return;
    }

    std::cout << "\nChoose agent type:\n";
    std::cout << "1. Worker\n";
    std::cout << "2. Trader\n";
    std::cout << "3. Student\n";

    int option = readInt("Type: ");
    AgentType type;

    switch (option) {
        case 1:
            type = AgentType::Worker;
            break;
        case 2:
            type = AgentType::Trader;
            break;
        case 3:
            type = AgentType::Student;
            break;
        default:
            std::cout << "Invalid agent type.\n";
            return;
    }

    std::unique_ptr<Agent> agent = AgentFactory::createAgent(type, generateNextAgentId());

    if (agent == nullptr) {
        std::cout << "Agent could not be created.\n";
        return;
    }

    std::cout << "Agent #" << agent->getId() << " created using AgentFactory.\n";
    world.addAgent(std::move(agent));
}

void Simulation::showAllAgents() const {
    const auto& agents = world.getAgents();

    std::cout << "\n--- All Agents ---\n";

    if (agents.empty()) {
        std::cout << "No agents in the world.\n";
    } else {
        for (const auto& agent : agents) {
            agent->display();
        }
    }

    std::cout << "------------------\n";
}

void Simulation::saveLoadMenu() {
    std::cout << "\n1. Save\n";
    std::cout << "2. Load\n";
    std::cout << "0. Back\n";

    int option = readInt("Choose option: ");

    if (option == 1) {
        if (saveManager.saveWorld(world, "data/save.txt")) {
            std::cout << "World saved successfully.\n";
        }
    } else if (option == 2) {
        if (saveManager.loadWorld(world, "data/save.txt")) {
            std::cout << "World loaded successfully.\n";
        } else {
            std::cout << "World could not be loaded.\n";
        }
    }
}

void Simulation::showEditConfigMenu() {
    SimulationConfig& config = SimulationConfig::getInstance();

    std::cout << "\n--- Config ---\n";
    std::cout << "1. maxTicks = " << config.getMaxTicks() << '\n';
    std::cout << "2. foodPrice = " << config.getFoodPrice() << '\n';
    std::cout << "3. maxAge = " << config.getMaxAge() << '\n';
    std::cout << "4. maxPopulation = " << config.getMaxPopulation() << '\n';
    std::cout << "5. reproductionChancePercent = " << config.getReproductionChancePercent() << '\n';
    std::cout << "6. ticksPerYear = " << config.getTicksPerYear() << '\n';
    std::cout << "7. adultAge = " << config.getAdultAge() << '\n';
    std::cout << "8. maxBirthsPerTick = " << config.getMaxBirthsPerTick() << '\n';
    std::cout << "9. livingCostPerTick = " << config.getLivingCostPerTick() << '\n';
    std::cout << "0. Back\n";

    int option = readInt("Choose value to edit: ");

    if (option == 0) {
        return;
    }

    int value = readInt("New value: ");
    std::string key;

    switch (option) {
        case 1:
            key = "maxTicks";
            break;
        case 2:
            key = "foodPrice";
            break;
        case 3:
            key = "maxAge";
            break;
        case 4:
            key = "maxPopulation";
            break;
        case 5:
            key = "reproductionChancePercent";
            break;
        case 6:
            key = "ticksPerYear";
            break;
        case 7:
            key = "adultAge";
            break;
        case 8:
            key = "maxBirthsPerTick";
            break;
        case 9:
            key = "livingCostPerTick";
            break;
        default:
            std::cout << "Invalid option.\n";
            return;
    }

    if (config.setValue(key, value)) {
        std::cout << "Config updated.\n";
    } else {
        std::cout << "Invalid config value.\n";
    }
}

void Simulation::update() {
    std::cout << "Simulation tick " << currentTick + 1 << "\n";
    world.update();
}

void Simulation::display() const {
    world.display();
    statisticsManager.displayStatistics(world);
    eventLogger.displayRecentEvents();
}