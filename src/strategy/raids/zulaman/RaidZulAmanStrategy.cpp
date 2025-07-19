#include "RaidZulAmanStrategy.h"

void RaidZulAmanStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(
        new TriggerNode("zulaman nalorakk",
            NextAction::array(0,
                new NextAction("zulaman nalorakk tank position", ACTION_MOVE + 1),
                nullptr)));
}

void RaidZulAmanStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
}
