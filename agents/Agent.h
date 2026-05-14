#ifndef MICROSOCIETY_AGENT_H
#define MICROSOCIETY_AGENT_H
#include "../core/Position.h"
#include <memory>
#include <string>

class World;

class Agent {
protected:
    int id;
    Position position;

    int hunger;
    int energy;
    int money;
    int happiness;

private:
    static int clampValue(int value, int minValue, int maxValue);

public:
    Agent(int id, const Position& position, int hunger, int energy, int money, int happiness);
    virtual ~Agent() = default;

    virtual void update(World& world) = 0;
    virtual void display() const = 0;
    virtual std::unique_ptr<Agent> clone() const = 0;
    virtual std::string getType() const = 0;

    int getId() const;
    Position getPosition() const;

    int getHunger() const;
    int getEnergy() const;
    int getMoney() const;
    int getHappiness() const;

    void setPosition(const Position& newPosition);
    void moveBy(int dx, int dy);

    void changeHunger(int amount);
    void changeEnergy(int amount);
    void changeMoney(int amount);
    void changeHappiness(int amount);
};

#endif //MICROSOCIETY_AGENT_H