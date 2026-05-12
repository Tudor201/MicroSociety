#ifndef MICROSOCIETY_MOVEACTION_H
#define MICROSOCIETY_MOVEACTION_H
#include "Action.h"

class MoveAction : public Action {
public:
    void execute(Agent& agent, World& world) override;
    std::string getName() const override;
};

#endif //MICROSOCIETY_MOVEACTION_H