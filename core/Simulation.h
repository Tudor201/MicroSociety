#ifndef MICROSOCIETY_SIMULATION_H
#define MICROSOCIETY_SIMULATION_H
#include "World.h"

class Simulation {
private:
    World world;
    bool running;
    int currentTick;

public:
    Simulation();

    void run();
    void update();
    void display() const;
};

#endif //MICROSOCIETY_SIMULATION_H