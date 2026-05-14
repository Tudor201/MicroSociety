#ifndef MICROSOCIETY_EVENTBUS_H
#define MICROSOCIETY_EVENTBUS_H
#include "Event.h"

#include <functional>
#include <map>
#include <vector>

class EventBus {
private:
    std::map<EventType, std::vector<std::function<void(const SimulationEvent&)>>> subscribers;

    EventBus() = default;

public:
    EventBus(const EventBus& other) = delete;
    EventBus& operator=(const EventBus& other) = delete;

    static EventBus& getInstance();

    void subscribe(EventType type, const std::function<void(const SimulationEvent&)>& callback);
    void publish(const SimulationEvent& event);
};

#endif //MICROSOCIETY_EVENTBUS_H