#include "RestAction.h"
#include "../agents/Agent.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"
#include <string>

void RestAction::execute(Agent& agent, World& world) {
    (void)world;

    agent.changeEnergy(30);
    agent.changeHunger(2);
    agent.changeHappiness(1);

    EventBus::getInstance().publish(
        SimulationEvent(
            EventType::AgentRested,
            agent.getId(),
            "Agent #" + std::to_string(agent.getId()) + " rested."
        )
    );
}

std::string RestAction::getName() const {
    return "Rest";
}