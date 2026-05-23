#include "Simulation.h"
#include "SimulationConfig.h"
#include "../patterns/AgentFactory.h"
#include "Exceptions.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

Simulation::Simulation()
    : running(false), currentTick(0) {
    try {
        if (saveManager.loadWorld(world, "data/save.txt")) {
            std::cout << "Loaded previous society from save file.\n";
        } else {
            world.spawnInitialAgents();
        }
    } catch (const MicroSocietyException& exception) {
        std::cout << "Save file error: " << exception.what() << '\n';
        std::cout << "Starting with a new world.\n";
        world.clearAgents();
        world.spawnInitialAgents();
    }
}

int Simulation::readInt(const std::string& message) const {
    int value;

    while (true) {
        std::cout << message;

        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void Simulation::clearScreen() const {
    std::cout << "\n\n";
}

void Simulation::waitForEnter() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

void Simulation::printHeader() const {
    std::cout << "\n========================================\n";
    std::cout << "           MicroSociety Simulator        \n";
    std::cout << "========================================\n";
    std::cout << "Tick: " << currentTick
              << " | Population: " << world.getAgentCount()
              << " | Map: " << world.getWidth() << "x" << world.getHeight()
              << '\n';
    std::cout << "----------------------------------------\n";
}

void Simulation::displayMainMenu() const {
    printHeader();
    std::cout << "1. Play simulation\n";
    std::cout << "2. Inspect society\n";
    std::cout << "3. Manage world\n";
    std::cout << "0. Exit\n";
}

void Simulation::displayPlayMenu() const {
    printHeader();
    std::cout << "1. Advance 1 tick\n";
    std::cout << "2. Advance 5 ticks\n";
    std::cout << "3. Advance custom number of ticks\n";
    std::cout << "0. Back\n";
}

void Simulation::displayInspectMenu() const {
    printHeader();
    std::cout << "1. Show map\n";
    std::cout << "2. Show statistics\n";
    std::cout << "3. Show agents\n";
    std::cout << "4. Show recent events\n";
    std::cout << "5. Full report\n";
    std::cout << "0. Back\n";
}

void Simulation::displayManageMenu() const {
    printHeader();
    std::cout << "1. Spawn agent manually\n";
    std::cout << "2. Save / Load\n";
    std::cout << "3. Show / edit config\n";
    std::cout << "0. Back\n";
}

void Simulation::run() {
    running = true;

    while (running) {
        clearScreen();
        displayMainMenu();

        switch (readInt("Choose option: ")) {
            case 1:
                playMenu();
                break;
            case 2:
                inspectMenu();
                break;
            case 3:
                manageMenu();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Invalid option.\n";
                waitForEnter();
                break;
        }
    }

    std::cout << "Exiting MicroSociety.\n";
}

void Simulation::playMenu() {
    bool inPlayMenu = true;

    while (inPlayMenu) {
        clearScreen();
        displayPlayMenu();

        switch (readInt("Choose option: ")) {
            case 1:
                runTicks(1);
                waitForEnter();
                break;
            case 2:
                runTicks(5);
                waitForEnter();
                break;
            case 3:
                runTicks();
                waitForEnter();
                break;
            case 0:
                inPlayMenu = false;
                break;
            default:
                std::cout << "Invalid option.\n";
                waitForEnter();
                break;
        }
    }
}

void Simulation::inspectMenu() const {
    bool inInspectMenu = true;

    while (inInspectMenu) {
        clearScreen();
        displayInspectMenu();

        switch (readInt("Choose option: ")) {
            case 1:
                world.displayMap();
                waitForEnter();
                break;
            case 2:
                statisticsManager.displayStatistics(world);
                waitForEnter();
                break;
            case 3:
                showAllAgents();
                waitForEnter();
                break;
            case 4:
                eventLogger.displayRecentEvents(10);
                waitForEnter();
                break;
            case 5:
                display();
                waitForEnter();
                break;
            case 0:
                inInspectMenu = false;
                break;
            default:
                std::cout << "Invalid option.\n";
                waitForEnter();
                break;
        }
    }
}

void Simulation::manageMenu() {
    bool inManageMenu = true;

    while (inManageMenu) {
        clearScreen();
        displayManageMenu();

        switch (readInt("Choose option: ")) {
            case 1:
                spawnAgentManual();
                waitForEnter();
                break;
            case 2:
                saveLoadMenu();
                waitForEnter();
                break;
            case 3:
                showEditConfigMenu();
                waitForEnter();
                break;
            case 0:
                inManageMenu = false;
                break;
            default:
                std::cout << "Invalid option.\n";
                waitForEnter();
                break;
        }
    }
}

void Simulation::runTicks() {
    runTicks(readInt("How many ticks? "));
}

void Simulation::runTicks(int ticks) {
    if (ticks <= 0) {
        std::cout << "Number of ticks must be positive.\n";
        return;
    }

    int maxTicks = SimulationConfig::getInstance().getMaxTicks();
    int ticksRun = 0;

    for (int i = 0; i < ticks && currentTick < maxTicks; i++) {
        update();
        currentTick++;
        ticksRun++;
    }

    showAfterTickReport(ticksRun);

    if (currentTick >= maxTicks) {
        std::cout << "Max ticks reached. Edit config to continue further.\n";
    }
}

void Simulation::showAfterTickReport(int ticksRun) const {
    std::cout << "\nSimulation advanced by " << ticksRun << " tick(s).\n";
    std::cout << "Current tick: " << currentTick << "\n";

    statisticsManager.displayStatistics(world);
    eventLogger.displayRecentEvents(5);
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

    AgentType type;

    switch (readInt("Type: ")) {
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

    std::cout << "Agent #" << agent->getId() << " created using AgentFactory.\n";
    world.addAgent(std::move(agent));
}

void Simulation::showAllAgents() const {
    const auto& agents = world.getAgents();

    std::cout << "\n--- Citizens ---\n";

    if (agents.empty()) {
        std::cout << "No agents in the world.\n";
    } else {
        for (const auto& agent : agents) {
            agent->display();
        }
    }

    std::cout << "----------------\n";
}

void Simulation::saveLoadMenu() {
    std::cout << "\n1. Save world\n";
    std::cout << "2. Load world\n";
    std::cout << "0. Back\n";

    int option = readInt("Choose option: ");

    if (option == 1) {
        if (saveManager.saveWorld(world, "data/save.txt")) {
            std::cout << "World saved successfully.\n";
        }
    } else if (option == 2) {
        try {
            if (saveManager.loadWorld(world, "data/save.txt")) {
                std::cout << "World loaded successfully.\n";
            } else {
                std::cout << "Save file does not exist.\n";
            }
        } catch (const MicroSocietyException& exception) {
            std::cout << "Load failed: " << exception.what() << '\n';
        }
    }
}

void Simulation::showEditConfigMenu() {
    SimulationConfig& config = SimulationConfig::getInstance();

    std::cout << "\n--- Configuration ---\n";
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
        std::cout << "Config updated for this run.\n";
    } else {
        std::cout << "Invalid config value.\n";
    }
}

void Simulation::update() {
    world.update();
}

void Simulation::display() const {
    world.display();
    statisticsManager.displayStatistics(world);
    eventLogger.displayRecentEvents(10);
}