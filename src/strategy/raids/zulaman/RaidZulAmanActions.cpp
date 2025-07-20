#include "Playerbots.h"
#include "RaidZulAmanActions.h"

bool ZulAmanTrashMarkTotemsAction::Execute(Event /*event*/)
{
    Unit* target = nullptr;
    Unit* medicineMan = AI_VALUE2(Unit*, "find target", "amani'shi medicine man");

    if (!medicineMan)
        return false;

    const GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");

    for (const auto& npcGuid : npcs)
    {
        Unit* unit = botAI->GetUnit(npcGuid);

        if (!unit)
            continue;

        if (unit->GetEntry() == NPC_AMANI_HEALING_WARD || unit->GetEntry() == NPC_AMANI_PROTECTIVE_WARD)
        {
            target = unit;
            break;
        }
    }

    if (!target)
        return false;

    if (Group* group = bot->GetGroup())
    {
        static constexpr uint8_t SKULL_ICON_INDEX = 7;
        const ObjectGuid currentSkull = group->GetTargetIcon(SKULL_ICON_INDEX);
        Unit* currentSkullUnit = botAI->GetUnit(currentSkull);

        if (!currentSkullUnit || !currentSkullUnit->IsAlive() || currentSkullUnit != target)
            group->SetTargetIcon(SKULL_ICON_INDEX, bot->GetGUID(), target->GetGUID());
    }

    return false;
}

bool ZulAmanNalorakkTankPositionAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "nalorakk");

    if (!boss)
        return false;

    if (!botAI->IsTank(bot))
        return false;

    if (botAI->HasAggro(boss) && boss->GetVictim() == bot)
    {
        // Move the boss into position
        float distanceToBossPosition = boss->GetExactDist2d(ZULAMAN_NALORAKK_BOSS_POSITION);

        if (distanceToBossPosition > 5.0f)
        {
            float dirX = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionX() - boss->GetPositionX();
            float dirY = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionY() - boss->GetPositionY();

            float moveX = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionX() + (dirX / distanceToBossPosition) * 4.0f;
            float moveY = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionY() + (dirY / distanceToBossPosition) * 4.0f;

            return MoveTo(bot->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false, false, false,
                          MovementPriority::MOVEMENT_FORCED, true, false);
        }

        // Make the boss face east
        float x = boss->GetPositionX();
        float y = boss->GetPositionY() - 3.0f;
        float z = bot->GetPositionZ();
        float distance = bot->GetExactDist2d(x, y);

        if (distance > 1.0f)
            return MoveTo(bot->GetMapId(), x, y, z, false, false, false, false, MovementPriority::MOVEMENT_FORCED, true,
                          false);
    }

    return false;
}

bool ZulAmanNalorakkRangedPositionAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "nalorakk");

    if (!boss)
        return false;

    if (boss->isMoving())
        return false;

    if (boss->GetExactDist2d(ZULAMAN_NALORAKK_BOSS_POSITION) > 5.0f)
        return false;

    if (!botAI->IsRanged(bot))
        return false;

    if (boss->isInFront(bot))
    {
        // Move upwards of 15 yards behind the boss
        float x = boss->GetPositionX();
        float y = boss->GetPositionY() + 15.0f;
        float z = bot->GetPositionZ();
    }

    return false;
}
