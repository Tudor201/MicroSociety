#ifndef MICROSOCIETY_DECISIONSTRATEGY_H
#define MICROSOCIETY_DECISIONSTRATEGY_H
#include <memory>

class Agent;
class World;
class Action;

class DecisionStrategy {
public:
    virtual ~DecisionStrategy() = default;

    virtual std::unique_ptr<Action> chooseAction(Agent& agent, World& world) = 0;
};

#endif //MICROSOCIETY_DECISIONSTRATEGY_H