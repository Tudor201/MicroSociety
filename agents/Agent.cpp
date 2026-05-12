#include "Agent.h"

int Agent::clampValue(int value, int minValue, int maxValue) {
    if (value < minValue) {
        return minValue;
    }

    if (value > maxValue) {
        return maxValue;
    }

    return value;
}

Agent::Agent(int id, const Position& position, int hunger, int energy, int money, int happiness)
    : id(id),
      position(position),
      hunger(clampValue(hunger, 0, 100)),
      energy(clampValue(energy, 0, 100)),
      money(money),
      happiness(clampValue(happiness, 0, 100)) {}

int Agent::getId() const {
    return id;
}

Position Agent::getPosition() const {
    return position;
}

int Agent::getHunger() const {
    return hunger;
}

int Agent::getEnergy() const {
    return energy;
}

int Agent::getMoney() const {
    return money;
}

int Agent::getHappiness() const {
    return happiness;
}

void Agent::setPosition(const Position& newPosition) {
    position = newPosition;
}

void Agent::moveBy(int dx, int dy) {
    position.x += dx;
    position.y += dy;
}

void Agent::changeHunger(int amount) {
    hunger = clampValue(hunger + amount, 0, 100);
}

void Agent::changeEnergy(int amount) {
    energy = clampValue(energy + amount, 0, 100);
}

void Agent::changeMoney(int amount) {
    money += amount;
}

void Agent::changeHappiness(int amount) {
    happiness = clampValue(happiness + amount, 0, 100);
}