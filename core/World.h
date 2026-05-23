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
    Grid<int> populationDensity;
    std::vector<std::unique_ptr<Agent>> agents;
    int nextAgentId;

    void recalculatePopulationDensity();
    bool canReproduce(const Agent& agent) const;
    std::unique_ptr<Agent> createChild(const Agent& parent1, const Agent& parent2);
    bool agentIsAlreadyParent(int id, const std::vector<int>& usedParentIds) const;

public:
    World();

    void spawnInitialAgents();
    void update();
    void display() const;
    void displayMap() const;

    void clearAgents();
    void addAgent(std::unique_ptr<Agent> agent);

    bool isInside(const Position& position) const;
    bool moveAgent(Agent& agent, int dx, int dy);

    int getAgentCount() const;
    int getWidth() const;
    int getHeight() const;

    void removeDeadAgents();
    void handleReproduction();
    void applyLivingCosts();

    const Grid<int>& getPopulationDensity() const;
    const std::vector<std::unique_ptr<Agent>>& getAgents() const;
};

#endif //MICROSOCIETY_WORLD_H