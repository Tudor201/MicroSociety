#include "WorkAction.h"
#include "../agents/Agent.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"

#include <string>

void WorkAction::execute(Agent& agent, World& world) {
    (void)world;

    if (!agent.isAdult()) {
        agent.changeHappiness(-1);

        EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentFailedAction,
                agent.getId(),
                "Agent #" + std::to_string(agent.getId()) + " is too young to work or trade."
            )
        );

        return;
    }

    std::string result = agent.performWork();

    EventBus::getInstance().publish(
        SimulationEvent(
            EventType::AgentWorked,
            agent.getId(),
            "Agent #" + std::to_string(agent.getId()) + " " + result
        )
    );
}

std::string WorkAction::getName() const {
    return "Work";
}