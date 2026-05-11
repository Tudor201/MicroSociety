#include "World.h"

#include <iostream>

World::World() {
    std::cout << "World created.\n";
}

void World::update() {
    std::cout << "World updated.\n";
}

void World::display() const {
    std::cout << "Displaying world.\n";
}