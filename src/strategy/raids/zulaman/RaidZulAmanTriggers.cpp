#include "Playerbots.h"
#include "RaidZulAmanTriggers.h"

bool ZulAmanTrashTrigger::IsActive()
{
    Unit* medicineMan = AI_VALUE2(Unit*, "find target", "amani'shi medicine man");

    if (!medicineMan)
        return false;

    return true;
}

bool ZulAmanNalorakkTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "nalorakk");

    if (!boss)
        return false;

    return true;
}

bool ZulAmanAkilzonTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "akil'zon");

    if (!boss)
        return false;

    return true;
}
