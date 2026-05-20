#ifndef MICROSOCIETY_EVENT_H
#define MICROSOCIETY_EVENT_H

#include <string>

enum class EventType {
    AgentSpawned,
    AgentChoseAction,
    AgentMoved,
    AgentWorked,
    AgentAte,
    AgentRested,
    AgentFailedAction,
    AgentDied,
    AgentBorn
};

class SimulationEvent {
private:
    EventType type;
    int agentId;
    std::string message;

public:
    SimulationEvent(EventType type, int agentId, const std::string& message)
        : type(type), agentId(agentId), message(message) {}

    EventType getType() const {
        return type;
    }

    int getAgentId() const {
        return agentId;
    }

    const std::string& getMessage() const {
        return message;
    }
};

#endif //MICROSOCIETY_EVENT_H