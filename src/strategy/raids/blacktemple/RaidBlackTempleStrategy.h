#ifndef _PLAYERBOT_RAIDBLACKTEMPLESTRATEGY_H_
#define _PLAYERBOT_RAIDBLACKTEMPLESTRATEGY_H_

#include "Strategy.h"

class RaidBlackTempleStrategy : public Strategy
{
public:
    RaidBlackTempleStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    std::string const getName() override { return "blacktemple"; }

    void InitTriggers(std::vector<TriggerNode*>& /*triggers*/) override;
    void InitMultipliers(std::vector<Multiplier*>& /*multipliers*/) override;
};

#endif
