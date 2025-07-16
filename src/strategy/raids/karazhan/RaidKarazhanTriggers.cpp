#include "Playerbots.h"
#include "RaidKarazhanTriggers.h"

bool KarazhanAttumenTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "attumen the huntsman");

    if (!boss)
        return false;

    return true;
}
