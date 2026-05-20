#include "EventBus.h"

EventBus& EventBus::getInstance() {
    static EventBus instance;
    return instance;
}

void EventBus::subscribe(EventType type, const std::function<void(const SimulationEvent&)>& callback) {
    subscribers[type].push_back(callback);
}

void EventBus::publish(const SimulationEvent& event) {
    auto it = subscribers.find(event.getType());

    if (it == subscribers.end()) {
        return;
    }

    for (const auto& callback : it->second) {
        callback(event);
    }
}