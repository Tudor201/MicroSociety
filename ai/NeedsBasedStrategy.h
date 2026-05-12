#ifndef MICROSOCIETY_NEEDSBASEDSTRATEGY_H
#define MICROSOCIETY_NEEDSBASEDSTRATEGY_H
#include "DecisionStrategy.h"

class NeedsBasedStrategy : public DecisionStrategy {
public:
    std::unique_ptr<Action> chooseAction(Agent& agent, World& world) override;
};

#endif //MICROSOCIETY_NEEDSBASEDSTRATEGY_H