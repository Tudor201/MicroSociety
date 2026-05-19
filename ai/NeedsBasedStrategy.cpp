#include "NeedsBasedStrategy.h"

#include "../agents/Agent.h"

#include "../actions/EatAction.h"
#include "../actions/RestAction.h"
#include "../actions/WorkAction.h"
#include "../actions/MoveAction.h"

#include "../core/SimulationConfig.h"

#include <memory>

std::unique_ptr<Action> NeedsBasedStrategy::chooseAction(Agent& agent, World& world) {
    (void)world;

    const int foodPrice = SimulationConfig::getInstance().getFoodPrice();

    if (agent.getHealth() < 45) {
        return std::make_unique<RestAction>();
    }

    if (agent.getEnergy() < 30) {
        return std::make_unique<RestAction>();
    }

    if (agent.getHunger() > 65) {
        if (agent.getMoney() >= foodPrice) {
            return std::make_unique<EatAction>();
        }

        if (agent.isAdult() && agent.canEarnMoney()) {
            return std::make_unique<WorkAction>();
        }

        return std::make_unique<MoveAction>();
    }

    if (!agent.isAdult()) {
        return std::make_unique<MoveAction>();
    }

    if (agent.canEarnMoney() && agent.getMoney() < 150) {
        return std::make_unique<WorkAction>();
    }

    if (agent.canWorkWithoutEarning() && agent.getEnergy() > 45 && agent.getHappiness() > 35 && agent.getMoney() > foodPrice + 5) {
        return std::make_unique<WorkAction>();
    }

    if (agent.getHappiness() < 35) {
        return std::make_unique<MoveAction>();
    }

    return std::make_unique<MoveAction>();
}