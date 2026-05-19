#include "NeedsBasedStrategy.h"

#include "../agents/Agent.h"
#include "../agents/WorkerAgent.h"
#include "../agents/TraderAgent.h"
#include "../agents/StudentAgent.h"

#include "../actions/EatAction.h"
#include "../actions/RestAction.h"
#include "../actions/WorkAction.h"
#include "../actions/MoveAction.h"

#include "../core/SimulationConfig.h"

#include <memory>

std::unique_ptr<Action> NeedsBasedStrategy::chooseAction(Agent& agent, World& world) {
    (void)world;

    const int foodPrice = SimulationConfig::getInstance().getFoodPrice();

    bool isWorker = dynamic_cast<WorkerAgent*>(&agent) != nullptr;
    bool isTrader = dynamic_cast<TraderAgent*>(&agent) != nullptr;
    bool isStudent = dynamic_cast<StudentAgent*>(&agent) != nullptr;

    bool canEarnMoney = isWorker || isTrader;

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

        if (agent.isAdult() && canEarnMoney) {
            return std::make_unique<WorkAction>();
        }

        return std::make_unique<MoveAction>();
    }

    if (!agent.isAdult()) {
        return std::make_unique<MoveAction>();
    }

    if (canEarnMoney && agent.getMoney() < 150) {
        return std::make_unique<WorkAction>();
    }

    if (isStudent && agent.getEnergy() > 45 && agent.getHappiness() > 35 && agent.getMoney() > foodPrice + 5) {
        return std::make_unique<WorkAction>();
    }

    if (agent.getHappiness() < 35) {
        return std::make_unique<MoveAction>();
    }

    return std::make_unique<MoveAction>();
}