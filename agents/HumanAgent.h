#ifndef MICROSOCIETY_HUMANAGENT_H
#define MICROSOCIETY_HUMANAGENT_H
#include "Agent.h"
#include <string>

class HumanAgent : public Agent {
protected:
    std::string name;

public:
    HumanAgent(int id, const std::string& name, const Position& position);
    ~HumanAgent() override = default;

    void update(World& world) override;
    void display() const override;

    const std::string& getName() const;
};

#endif //MICROSOCIETY_HUMANAGENT_H