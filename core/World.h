#ifndef MICROSOCIETY_WORLD_H
#define MICROSOCIETY_WORLD_H
#include "../agents/Agent.h"

#include <memory>
#include <vector>

class World {
private:
    std::vector<std::unique_ptr<Agent>> agents;

public:
    World();

    void spawnInitialAgents();
    void update();
    void display() const;

    int getAgentCount() const;
};

#endif //MICROSOCIETY_WORLD_H