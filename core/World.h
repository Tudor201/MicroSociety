#ifndef MICROSOCIETY_WORLD_H
#define MICROSOCIETY_WORLD_H
#include "Grid.h"
#include "CellType.h"
#include "Position.h"
#include "../agents/Agent.h"

#include <memory>
#include <vector>

class World {
private:
    int width;
    int height;
    Grid<CellType> terrain;
    std::vector<std::unique_ptr<Agent>> agents;

public:
    World();

    void spawnInitialAgents();
    void update();
    void display() const;

    bool isInside(const Position& position) const;
    bool moveAgent(Agent& agent, int dx, int dy);

    int getAgentCount() const;
    int getWidth() const;
    int getHeight() const;
};

#endif //MICROSOCIETY_WORLD_H