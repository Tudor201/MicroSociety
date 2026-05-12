#ifndef MICROSOCIETY_EATACTION_H
#define MICROSOCIETY_EATACTION_H
#include "Action.h"

class EatAction : public Action {
public:
    void execute(Agent& agent, World& world) override;
    std::string getName() const override;
};

#endif //MICROSOCIETY_EATACTION_H