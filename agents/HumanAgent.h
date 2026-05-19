#ifndef MICROSOCIETY_HUMANAGENT_H
#define MICROSOCIETY_HUMANAGENT_H
#include "Agent.h"
#include <memory>
#include <string>

class DecisionStrategy;

class HumanAgent : public Agent {
protected:
    std::string name;
    std::shared_ptr<DecisionStrategy> strategy;
    std::weak_ptr<DecisionStrategy> strategyObserver;

public:
    HumanAgent(int id, const std::string& name, const Position& position);
    ~HumanAgent() override = default;

    void update(World& world) override;
    void display() const override;
    std::string performWork() override = 0;
    bool canEarnMoney() const override = 0;
    bool canWorkWithoutEarning() const override = 0;

    const std::string& getName() const;
};

#endif //MICROSOCIETY_HUMANAGENT_H