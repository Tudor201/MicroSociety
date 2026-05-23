#include "EatAction.h"
#include "../agents/Agent.h"
#include "../core/SimulationConfig.h"
#include "../patterns/EventBus.h"
#include "../patterns/Event.h"
#include <string>

void EatAction::execute(Agent& agent, World& world) {
    (void)world;

    const int foodPrice = SimulationConfig::getInstance().getFoodPrice();

    if (agent.getMoney() >= foodPrice) {
        agent.changeMoney(-foodPrice);
        agent.changeHunger(-35);
        agent.changeEnergy(5);
        agent.changeHappiness(3);

        EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentAte,
                agent.getId(),
                "Agent #" + std::to_string(agent.getId()) + " ate food."
            )
        );
    } else {
        agent.changeHappiness(-5);

        EventBus::getInstance().publish(
            SimulationEvent(
                EventType::AgentFailedAction,
                agent.getId(),
                "Agent #" + std::to_string(agent.getId()) + " wanted to eat but did not have enough money."
            )
        );
    }
}

std::string EatAction::getName() const {
    return "Eat";
}