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

    int health;
    int age;
    int ticksLived;
    bool alive;

private:
    static int clampValue(int value, int minValue, int maxValue);

public:
    Agent(
        int id,
        const Position& position,
        int hunger,
        int energy,
        int money,
        int happiness,
        int health = 100,
        int age = 18
    );

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
    int getHealth() const;
    int getAge() const;
    int getTicksLived() const;

    bool isAlive() const;
    bool isAdult() const;

    void setPosition(const Position& newPosition);
    void setAge(int newAge);
    void setTicksLived(int newTicksLived);

    void moveBy(int dx, int dy);

    void changeHunger(int amount);
    void changeEnergy(int amount);
    void changeMoney(int amount);
    void changeHappiness(int amount);
    void changeHealth(int amount);

    void updateLifeStatus();
};

#endif //MICROSOCIETY_AGENT_H