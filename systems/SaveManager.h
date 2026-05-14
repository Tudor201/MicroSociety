#ifndef MICROSOCIETY_SAVEMANAGER_H
#define MICROSOCIETY_SAVEMANAGER_H
#include <string>

class World;

class SaveManager {
public:
    SaveManager() = default;

    bool saveWorld(const World& world, const std::string& filePath) const;
    bool loadWorld(World& world, const std::string& filePath) const;
};

#endif //MICROSOCIETY_SAVEMANAGER_H