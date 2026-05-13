#ifndef MICROSOCIETY_AGENTFACTORY_H
#define MICROSOCIETY_AGENTFACTORY_H

#include <memory>

class Agent;

enum class AgentType {
    Worker, Trader, Student
};

class AgentFactory {
public:
    static std::unique_ptr<Agent> createAgent(AgentType type, int id);
};

#endif //MICROSOCIETY_AGENTFACTORY_H