#ifndef MICROSOCIETY_EVENTLOGGER_H
#define MICROSOCIETY_EVENTLOGGER_H
#include "../patterns/Event.h"

#include <string>
#include <vector>

class EventLogger {
private:
    std::vector<std::string> recentEvents;
    int maxStoredEvents;

    void subscribeTo(EventType type);
    void logEvent(const SimulationEvent& event);

public:
    EventLogger();

    void displayRecentEvents(int count = 5) const;
};

#endif //MICROSOCIETY_EVENTLOGGER_H