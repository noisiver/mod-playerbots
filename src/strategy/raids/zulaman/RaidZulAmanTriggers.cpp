#include "Playerbots.h"
#include "RaidZulAmanTriggers.h"

bool ZulAmanNalorakkTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "nalorakk");

    if (!boss)
        return false;

    return true;
}

