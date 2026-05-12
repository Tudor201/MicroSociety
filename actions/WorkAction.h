#ifndef MICROSOCIETY_WORKACTION_H
#define MICROSOCIETY_WORKACTION_H
#include "Action.h"

class WorkAction : public Action {
public:
    void execute(Agent& agent, World& world) override;
    std::string getName() const override;
};

#endif //MICROSOCIETY_WORKACTION_H