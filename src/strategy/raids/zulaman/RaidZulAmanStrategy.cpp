#include "RaidZulAmanStrategy.h"

void RaidZulAmanStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(
        new TriggerNode("zulaman trash", NextAction::array(0,
                new NextAction("zulaman trash mark totems", ACTION_RAID + 1),
                nullptr)));

    triggers.push_back(
        new TriggerNode("zulaman nalorakk", NextAction::array(0,
                new NextAction("zulaman nalorakk tank position", ACTION_MOVE + 1),
                new NextAction("zulaman nalorakk ranged position", ACTION_MOVE + 2),
                nullptr)));
}

void RaidZulAmanStrategy::InitMultipliers(std::vector<Multiplier*>& /*multipliers*/)
{
}
