#ifndef MICROSOCIETY_RESTACTION_H
#define MICROSOCIETY_RESTACTION_H
#include "Action.h"

class RestAction : public Action {
public:
    void execute(Agent& agent, World& world) override;
    std::string getName() const override;
};

#endif //MICROSOCIETY_RESTACTION_H