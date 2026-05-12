#ifndef MICROSOCIETY_WORKERAGENT_H
#define MICROSOCIETY_WORKERAGENT_H

#include "HumanAgent.h"
#include <string>

class WorkerAgent : public HumanAgent {
private:
    int salary;
    std::string jobName;

public:
    WorkerAgent(int id, const std::string& name, const Position& position, int salary, const std::string& jobName);

    void update(World& world) override;
    void display() const override;
    std::unique_ptr<Agent> clone() const override;

    void earnMoney();
    int getSalary() const;
};

#endif //MICROSOCIETY_WORKERAGENT_H