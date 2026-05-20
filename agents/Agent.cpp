#include "Agent.h"
#include "../core/SimulationConfig.h"

int Agent::clampValue(int value, int minValue, int maxValue) {
    if (value < minValue) {
        return minValue;
    }

    if (value > maxValue) {
        return maxValue;
    }

    return value;
}

Agent::Agent(
    int id,
    const Position& position,
    int hunger,
    int energy,
    int money,
    int happiness,
    int health,
    int age
)
    : id(id),
      position(position),
      hunger(clampValue(hunger, 0, 100)),
      energy(clampValue(energy, 0, 100)),
      money(money),
      happiness(clampValue(happiness, 0, 100)),
      health(clampValue(health, 0, 100)),
      age(age),
      ticksLived(0),
      alive(true) {}

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

int Agent::getHealth() const {
    return health;
}

int Agent::getAge() const {
    return age;
}

int Agent::getTicksLived() const {
    return ticksLived;
}

bool Agent::isAlive() const {
    return alive;
}

bool Agent::isAdult() const {
    return age >= SimulationConfig::getInstance().getAdultAge();
}

void Agent::setPosition(const Position& newPosition) {
    position = newPosition;
}

void Agent::setAge(int newAge) {
    if (newAge < 0) {
        age = 0;
    } else {
        age = newAge;
    }
}

void Agent::setTicksLived(int newTicksLived) {
    if (newTicksLived < 0) {
        ticksLived = 0;
    } else {
        ticksLived = newTicksLived;
    }
}

void Agent::moveBy(int dx, int dy) {
    position.moveBy(dx, dy);
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

void Agent::changeHealth(int amount) {
    health = clampValue(health + amount, 0, 100);

    if (health == 0) {
        alive = false;
    }
}

void Agent::updateLifeStatus() {
    ticksLived++;

    int ticksPerYear = SimulationConfig::getInstance().getTicksPerYear();

    if (ticksPerYear <= 0) {
        ticksPerYear = 12;
    }

    if (ticksLived % ticksPerYear == 0) {
        age++;
    }

    if (hunger > 80) {
        changeHealth(-5);
    }

    if (energy < 20) {
        changeHealth(-3);
    }

    if (happiness < 20) {
        changeHealth(-2);
    }

    if (hunger < 50 && energy > 40 && happiness > 40) {
        changeHealth(1);
    }
}