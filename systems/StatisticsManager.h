#ifndef MICROSOCIETY_STATISTICSMANAGER_H
#define MICROSOCIETY_STATISTICSMANAGER_H

class World;

class StatisticsManager {
public:
    StatisticsManager() = default;

    void displayStatistics(const World& world) const;
};

#endif //MICROSOCIETY_STATISTICSMANAGER_H