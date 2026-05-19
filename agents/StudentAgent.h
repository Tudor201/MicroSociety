#ifndef MICROSOCIETY_STUDENTAGENT_H
#define MICROSOCIETY_STUDENTAGENT_H
#include "HumanAgent.h"

#include <memory>
#include <string>

class StudentAgent : public HumanAgent {
private:
    std::string university;
    int knowledgeLevel;

public:
    StudentAgent(int id, const std::string& name, const Position& position, const std::string& university);

    void update(World& world) override;
    void display() const override;
    std::unique_ptr<Agent> clone() const override;
    std::string getType() const override;

    void study();
    int getKnowledgeLevel() const;
    const std::string& getUniversity() const;
    void setKnowledgeLevel(int newKnowledgeLevel);
};

#endif //MICROSOCIETY_STUDENTAGENT_H