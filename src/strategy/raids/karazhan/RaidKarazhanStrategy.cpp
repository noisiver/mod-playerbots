#include "RaidKarazhanStrategy.h"

void RaidKarazhanStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(
        new TriggerNode("karazhan attumen",
            NextAction::array(0, new NextAction("karazhan attumen stay close", ACTION_RAID + 2),
                                 nullptr)));
}

void RaidKarazhanStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
}
