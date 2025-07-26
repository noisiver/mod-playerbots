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

        triggers.push_back(
        new TriggerNode("zulaman akilzon", NextAction::array(0,
                new NextAction("zulaman akilzon electrical storm", ACTION_EMERGENCY + 1),
                new NextAction("zulaman akilzon tank position", ACTION_MOVE + 1),
                new NextAction("zulaman akilzon ranged position", ACTION_MOVE + 2),
                nullptr)));
}

void RaidZulAmanStrategy::InitMultipliers(std::vector<Multiplier*>& /*multipliers*/)
{
}
