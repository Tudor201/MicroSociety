#ifndef MICROSOCIETY_TRADERAGENT_H
#define MICROSOCIETY_TRADERAGENT_H
#include "HumanAgent.h"

#include <memory>
#include <string>

class TraderAgent : public HumanAgent {
private:
    int profitPerTrade;

public:
    TraderAgent(int id, const std::string& name, const Position& position, int profitPerTrade);

    void update(World& world) override;
    void display() const override;
    std::unique_ptr<Agent> clone() const override;
    std::string getType() const override;
    std::string performWork() override;
    bool canEarnMoney() const override;
    bool canWorkWithoutEarning() const override;

    void makeTrade();
    int getProfitPerTrade() const;
};

#endif //MICROSOCIETY_TRADERAGENT_H