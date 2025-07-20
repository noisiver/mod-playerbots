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

    if (!(botAI->HasAggro(boss) && boss->GetVictim() == bot))
        return false;

    float distanceToBossPosition = boss->GetExactDist2d(ZULAMAN_NALORAKK_BOSS_POSITION);

    if (distanceToBossPosition > 5.0f)
    {
        float directionX = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionX() - boss->GetPositionX();
        float directionY = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionY() - boss->GetPositionY();

        float moveX = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionX() + (directionX / distanceToBossPosition) * 4.0f;
        float moveY = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionY() + (directionY / distanceToBossPosition) * 4.0f;

        return MoveTo(bot->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false, false, false,
                        MovementPriority::MOVEMENT_FORCED, true, false);
    }

    float x = boss->GetPositionX();
    float y = boss->GetPositionY() - 3.0f;
    float z = bot->GetPositionZ();
    float distance = bot->GetExactDist2d(x, y);

    if (distance > 1.0f)
        return MoveTo(bot->GetMapId(), x, y, z, false, false, false, false, MovementPriority::MOVEMENT_FORCED, true,
                        false);

    return false;
}

bool ZulAmanNalorakkRangedPositionAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "nalorakk");

    if (!boss)
        return false;

    if (!botAI->IsRanged(bot))
        return false;

    if (bot->GetPositionY() < ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionY())
    {
        float x = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionX();
        float y = ZULAMAN_NALORAKK_BOSS_POSITION.GetPositionY() + urand(8.0f, 15.0f);
        float z = bot->GetPositionZ();

        float variation = urand(4.0f, 8.0f);
        if (bot->GetPositionX() > x)
            x += variation;
        else
            x -= variation;

        return MoveTo(bot->GetMapId(), x, y, z, false, false, false, false, MovementPriority::MOVEMENT_FORCED, true,
                      false);
    }

    const GuidVector members = AI_VALUE(GuidVector, "group members");
    const float safeSpacingRadius = 10.0f;
    const float moveIncrement = 2.0f;
    const float maxMoveDistance = 5.0f;
    float totalX = 0.0f;
    float totalY = 0.0f;
    int nearbyCount = 0;

    for (const auto& memberGuid : members)
    {
        Unit* member = botAI->GetUnit(memberGuid);

        if (!member || !member->IsAlive() || member == bot || !botAI->IsRanged(bot))
            continue;

        const float distance = bot->GetExactDist2d(member);
        if (distance < safeSpacingRadius)
        {
            float dx = bot->GetPositionX() - member->GetPositionX();
            float dy = bot->GetPositionY() - member->GetPositionY();

            float weight = (safeSpacingRadius - distance) / safeSpacingRadius;
            totalX += dx * weight;
            totalY += dy * weight;
            nearbyCount++;
        }
    }

    if (nearbyCount > 0)
    {
        float magnitude = std::sqrt(totalX * totalX + totalY * totalY);
        if (magnitude > 0.001f)
        {
            totalX /= magnitude;
            totalY /= magnitude;

            float moveDistance = std::min(moveIncrement, maxMoveDistance);

            float targetX = bot->GetPositionX() + totalX * moveDistance;
            float targetY = bot->GetPositionY() + totalY * moveDistance;
            float targetZ = bot->GetPositionZ();

            if (bot->IsWithinLOS(targetX, targetY, targetZ))
            {
                Position targetPos(targetX, targetY, targetZ);
                return MoveTo(bot->GetMapId(), targetPos.GetPositionX(), targetPos.GetPositionY(), targetPos.GetPositionZ(),
                       false, false, false, true, MovementPriority::MOVEMENT_NORMAL);
            }
            else
            {
                targetX = bot->GetPositionX() + totalX * (moveDistance * 0.5f);
                targetY = bot->GetPositionY() + totalY * (moveDistance * 0.5f);
                Position targetPos(targetX, targetY, targetZ);
                return MoveTo(bot->GetMapId(), targetPos.GetPositionX(), targetPos.GetPositionY(), targetPos.GetPositionZ(),
                       false, false, false, true, MovementPriority::MOVEMENT_NORMAL);
            }
        }
    }

    return false;
}

bool ZulAmanAkilzonElectricalStormAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "akil'zon");

    if (!boss)
        return false;

    if (!(boss->HasUnitState(UNIT_STATE_CASTING) && boss->FindCurrentSpellBySpellId(SPELL_ELECTRICAL_STORM)))
        return false;

    Unit* target = boss->FindCurrentSpellBySpellId(SPELL_ELECTRICAL_STORM)->m_targets.GetUnitTarget();

    if (!target)
        return false;

    bot->InterruptNonMeleeSpells(false);
    bot->AttackStop();

    return MoveTo(bot->GetMapId(), target->GetPositionX(), target->GetPositionY(), bot->GetPositionZ(), false,
                    false, false, true, MovementPriority::MOVEMENT_FORCED);
}

bool ZulAmanAkilzonTankPositionAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "akil'zon");

    if (!boss)
        return false;

    if (boss->HasUnitState(UNIT_STATE_CASTING) && boss->FindCurrentSpellBySpellId(SPELL_ELECTRICAL_STORM))
        return false;

    if (!botAI->IsTank(bot))
        return false;

    if (!(botAI->HasAggro(boss) && boss->GetVictim() == bot))
        return false;

    float distanceToBossPosition = boss->GetExactDist2d(ZULAMAN_AKILZON_BOSS_POSITION);

    if (distanceToBossPosition > 5.0f)
    {
        float directionX = ZULAMAN_AKILZON_BOSS_POSITION.GetPositionX() - boss->GetPositionX();
        float directionY = ZULAMAN_AKILZON_BOSS_POSITION.GetPositionY() - boss->GetPositionY();

        float moveX = ZULAMAN_AKILZON_BOSS_POSITION.GetPositionX() + (directionX / distanceToBossPosition) * 4.0f;
        float moveY = ZULAMAN_AKILZON_BOSS_POSITION.GetPositionY() + (directionY / distanceToBossPosition) * 4.0f;

        return MoveTo(bot->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false, false, false,
                      MovementPriority::MOVEMENT_FORCED, true, false);
    }

    return false;
}

bool ZulAmanAkilzonRangedPositionAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "akil'zon");

    if (!boss)
        return false;

    if (boss->HasUnitState(UNIT_STATE_CASTING) && boss->FindCurrentSpellBySpellId(SPELL_ELECTRICAL_STORM))
        return false;

    if (!botAI->IsRanged(bot))
        return false;

    return false;
}
