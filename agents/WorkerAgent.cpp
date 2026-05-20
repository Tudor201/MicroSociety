#include "WorkerAgent.h"
#include <iostream>
#include <memory>

WorkerAgent::WorkerAgent(int id, const std::string& name, const Position& position, int salary, const std::string& jobName)
    : HumanAgent(id, name, position),
      salary(salary),
      jobName(jobName) {}

void WorkerAgent::update(World& world) {
    HumanAgent::update(world);
}

void WorkerAgent::display() const {
    std::cout << "WorkerAgent #" << id
              << " | Name: " << name
              << " | Job: " << jobName
              << " | Position: (" << position.getX() << ", " << position.getY() << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << " | Health: " << health
              << " | Age: " << age
              << '\n';
}

std::unique_ptr<Agent> WorkerAgent::clone() const {
    return std::make_unique<WorkerAgent>(*this);
}

std::string WorkerAgent::performWork() {
    earnMoney();

    changeHunger(7);
    changeEnergy(-10);
    changeHappiness(1);

    return "worked and earned money.";
}

bool WorkerAgent::canEarnMoney() const {
    return true;
}

bool WorkerAgent::canWorkWithoutEarning() const {
    return false;
}

void WorkerAgent::earnMoney() {
    changeMoney(salary);
}

int WorkerAgent::getSalary() const {
    return salary;
}

std::string WorkerAgent::getType() const {
    return "Worker";
}

const std::string& WorkerAgent::getJobName() const {
    return jobName;
}