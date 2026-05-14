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
              << " | Position: (" << position.x << ", " << position.y << ")"
              << " | Hunger: " << hunger
              << " | Energy: " << energy
              << " | Money: " << money
              << " | Happiness: " << happiness
              << " | Profit/Trade: " << profitPerTrade
              << '\n';
}

std::unique_ptr<Agent> TraderAgent::clone() const {
    return std::make_unique<TraderAgent>(*this);
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