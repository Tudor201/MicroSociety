#include "StudentAgent.h"
#include <iostream>
#include <memory>

StudentAgent::StudentAgent(int id, const std::string& name, const Position& position, const std::string& university)
    : HumanAgent(id, name, position),
      university(university),
      knowledgeLevel(0) {}

void StudentAgent::update(World& world) {
    HumanAgent::update(world);
}

void StudentAgent::display() const {
    std::cout << "StudentAgent #" << id
              << " | Name: " << name
              << " | University: " << university
              << " | Position: (" << position.getX() << ", " << position.getY() << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << " | Health: " << health
              << " | Age: " << age
              << " | Knowledge: " << knowledgeLevel
              << '\n';
}

std::unique_ptr<Agent> StudentAgent::clone() const {
    return std::make_unique<StudentAgent>(*this);
}

std::string StudentAgent::performWork() {
    study();

    changeHunger(4);
    changeEnergy(-7);
    changeMoney(-2);

    return "studied.";
}

bool StudentAgent::canEarnMoney() const {
    return false;
}

bool StudentAgent::canWorkWithoutEarning() const {
    return true;
}

void StudentAgent::study() {
    knowledgeLevel += 10;
    changeHappiness(2);
}

int StudentAgent::getKnowledgeLevel() const {
    return knowledgeLevel;
}

std::string StudentAgent::getType() const {
    return "Student";
}

const std::string& StudentAgent::getUniversity() const {
    return university;
}

void StudentAgent::setKnowledgeLevel(int newKnowledgeLevel) {
    if (newKnowledgeLevel < 0) {
        knowledgeLevel = 0;
    } else {
        knowledgeLevel = newKnowledgeLevel;
    }
}