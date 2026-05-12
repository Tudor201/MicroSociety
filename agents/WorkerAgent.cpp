#include "WorkerAgent.h"
#include <iostream>
#include <memory>

WorkerAgent::WorkerAgent(int id, const std::string& name, const Position& position, int salary, const std::string& jobName)
    : HumanAgent(id, name, position),
      salary(salary),
      jobName(jobName) {}

void WorkerAgent::update(World& world) {
    (void)world;

    earnMoney();

    changeHunger(7);
    changeEnergy(-10);
    changeHappiness(1);
    moveBy(1, 0);

    std::cout << name << " worked as " << jobName << " and earned " << salary << " money.\n";
}

void WorkerAgent::display() const {
    std::cout << "WorkerAgent #" << id
              << " | Name: " << name
              << " | Job: " << jobName
              << " | Position: (" << position.x << ", " << position.y << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << '\n';
}

std::unique_ptr<Agent> WorkerAgent::clone() const {
    return std::make_unique<WorkerAgent>(*this);
}

void WorkerAgent::earnMoney() {
    changeMoney(salary);
}

int WorkerAgent::getSalary() const {
    return salary;
}