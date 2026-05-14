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
              << " | Position: (" << position.x << ", " << position.y << ")"
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