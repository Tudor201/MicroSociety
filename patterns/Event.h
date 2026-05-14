#ifndef MICROSOCIETY_EVENT_H
#define MICROSOCIETY_EVENT_H

#include <string>

enum class EventType {
    AgentSpawned,
    AgentMoved,
    AgentWorked,
    AgentAte,
    AgentRested,
    AgentFailedAction,
    AgentDied,
    AgentBorn
};

struct SimulationEvent {
    EventType type;
    int agentId;
    std::string message;

    SimulationEvent(EventType type, int agentId, const std::string& message)
        : type(type), agentId(agentId), message(message) {}
};

#endif //MICROSOCIETY_EVENT_H