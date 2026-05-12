#ifndef MICROSOCIETY_ACTION_H
#define MICROSOCIETY_ACTION_H
#include <string>

class Agent;
class World;

class Action {
public:
    virtual ~Action() = default;

    virtual void execute(Agent& agent, World& world) = 0;
    virtual std::string getName() const = 0;
};

#endif //MICROSOCIETY_ACTION_H