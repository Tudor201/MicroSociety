#include "TraderAgent.h"
#include <iostream>
#include <memory>

TraderAgent::TraderAgent(int id, const std::string& name, const Position& position, int profitPerTrade)
    : HumanAgent(id, name, position),
      profitPerTrade(profitPerTrade) {}

void TraderAgent::update(World& world) {
    HumanAgent::update(world);
}

void TraderAgent::display() const {
    std::cout << "TraderAgent #" << id
              << " | Name: " << name
              << " | Position: (" << position.getX() << ", " << position.getY() << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << " | Health: " << health
              << " | Age: " << age
              << " | Profit/Trade: " << profitPerTrade
              << '\n';
}

std::unique_ptr<Agent> TraderAgent::clone() const {
    return std::make_unique<TraderAgent>(*this);
}

std::string TraderAgent::performWork() {
    makeTrade();

    changeHunger(5);
    changeEnergy(-8);
    changeHappiness(2);

    return "made a trade.";
}

bool TraderAgent::canEarnMoney() const {
    return true;
}

bool TraderAgent::canWorkWithoutEarning() const {
    return false;
}

void TraderAgent::makeTrade() {
    changeMoney(profitPerTrade);
}

int TraderAgent::getProfitPerTrade() const {
    return profitPerTrade;
}

std::string TraderAgent::getType() const {
    return "Trader";
}