#include "NeedsBasedStrategy.h"
#include "../agents/Agent.h"
#include "../actions/EatAction.h"
#include "../actions/RestAction.h"
#include "../actions/WorkAction.h"
#include "../actions/MoveAction.h"

#include <memory>

std::unique_ptr<Action> NeedsBasedStrategy::chooseAction(Agent& agent, World& world) {
    (void)world;

    if (agent.getEnergy() < 35) {
        return std::make_unique<RestAction>();
    }

    if (agent.getHunger() > 60) {
        return std::make_unique<EatAction>();
    }

    if (agent.getMoney() < 150) {
        return std::make_unique<WorkAction>();
    }

    return std::make_unique<MoveAction>();
}