#include "EventLogger.h"
#include "../patterns/EventBus.h"
#include "../core/SimulationConfig.h"

#include <iostream>

EventLogger::EventLogger()
    : maxStoredEvents(SimulationConfig::getInstance().getMaxStoredEvents()) {
    subscribeTo(EventType::AgentSpawned);
    subscribeTo(EventType::AgentChoseAction);
    subscribeTo(EventType::AgentMoved);
    subscribeTo(EventType::AgentWorked);
    subscribeTo(EventType::AgentAte);
    subscribeTo(EventType::AgentRested);
    subscribeTo(EventType::AgentFailedAction);
    subscribeTo(EventType::AgentDied);
    subscribeTo(EventType::AgentBorn);
}

void EventLogger::subscribeTo(EventType type) {
    EventBus::getInstance().subscribe(
        type,
        [this](const SimulationEvent& event) {
            logEvent(event);
        }
    );
}

void EventLogger::logEvent(const SimulationEvent& event) {
    recentEvents.push_back(event);

    if (static_cast<int>(recentEvents.size()) > maxStoredEvents) {
        recentEvents.erase(recentEvents.begin());
    }
}

void EventLogger::displayRecentEvents(int count) const {
    std::cout << "\n--- Recent Events ---\n";

    if (recentEvents.empty()) {
        std::cout << "No events recorded yet.\n";
        std::cout << "---------------------\n\n";
        return;
    }

    int start = static_cast<int>(recentEvents.size()) - count;

    if (start < 0) {
        start = 0;
    }

    for (int i = start; i < static_cast<int>(recentEvents.size()); i++) {
        std::cout << "- Agent #" << recentEvents[i].getAgentId()
          << ": " << recentEvents[i].getMessage() << '\n';
    }

    std::cout << "---------------------\n\n";
}