#include "Playerbots.h"
#include "RaidKarazhanActions.h"

bool KarazhanMoroesMarkTargetAction::Execute(Event event)
{
    Unit* target = nullptr;
    Unit* dorothea = AI_VALUE2(Unit*, "find target", "baroness dorothea millstipe");
    Unit* catriona = AI_VALUE2(Unit*, "find target", "lady catriona von'indi");
    Unit* keira = AI_VALUE2(Unit*, "find target", "lady keira berrybuck");
    Unit* rafe = AI_VALUE2(Unit*, "find target", "baron rafe dreuger");
    Unit* robin = AI_VALUE2(Unit*, "find target", "lord robin daris");
    Unit* crispin = AI_VALUE2(Unit*, "find target", "lord crispin ference");

    if (dorothea && dorothea->IsAlive())
        target = dorothea;
    else if (catriona && catriona->IsAlive())
        target = catriona;
    else if (keira && keira->IsAlive())
        target = keira;
    else if (rafe && rafe->IsAlive())
        target = rafe;
    else if (robin && robin->IsAlive())
        target = robin;
    else if (crispin && crispin->IsAlive())
        target = crispin;

    if (!target)
        return false;

    if (Group* group = bot->GetGroup())
    {
        constexpr uint8_t skullIconId = 7;
        ObjectGuid skullGuid = group->GetTargetIcon(skullIconId);

        if (skullGuid != target->GetGUID())
            group->SetTargetIcon(skullIconId, bot->GetGUID(), target->GetGUID());
    }

    return false;
}

bool KarazhanMaidenOfVirtuePositionBossAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "maiden of virtue");

    if (!boss)
        return false;

    if (!botAI->IsTank(bot))
        return false;

    Unit* healer = nullptr;

    if (Group* group = bot->GetGroup())
    {
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* member = itr->GetSource();

            if (!member || !member->IsAlive() || !botAI->IsHeal(member))
                continue;

            if (!member->HasAura(SPELL_REPENTANCE))
                break;

            healer = member;
            break;
        }
    }

    if (botAI->HasAggro(boss) && boss->GetVictim() == bot)
    {
        Position position = KARAZHAN_MAIDEN_OF_VIRTUE_BOSS_POSITION;

        if (healer)
            position = healer->GetPosition();

        const float distanceToPosition = boss->GetExactDist2d(position);

        if (distanceToPosition > 5.0f)
        {
            float dirX = position.GetPositionX() - boss->GetPositionX();
            float dirY = position.GetPositionY() - boss->GetPositionY();

            float moveX = position.GetPositionX() + (dirX / distanceToPosition) * 4.0f;
            float moveY = position.GetPositionY() + (dirY / distanceToPosition) * 4.0f;

            return MoveTo(bot->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false, false, false,
                          MovementPriority::MOVEMENT_FORCED, true, false);
        }
    }

    return false;
}

bool KarazhanMaidenOfVirtuePositionRangedAction::Execute(Event /*event*/)
{
    if (!botAI->IsRanged(bot))
        return false;

    int maxIndex = 7;
    int index = 0;

    const GuidVector members = AI_VALUE(GuidVector, "group members");

    for (const auto& memberGuid : members)
    {
        Unit* member = botAI->GetUnit(memberGuid);

        if (!member || !botAI->IsRanged(member->ToPlayer()))
            continue;

        if (member == bot)
            break;

        // Reset index to 0 if there are more than 8 ranged players
        if (index >= maxIndex)
        {
            index = 0;
            continue;
        }

        index++;
    }

    float distance = bot->GetExactDist2d(KARAZHAN_MAIDEN_OF_VIRTUE_RANGED_POSITION[index]);
    const float maxDistance = 2.0f;

    if (distance > maxDistance)
        return MoveTo(bot->GetMapId(), KARAZHAN_MAIDEN_OF_VIRTUE_RANGED_POSITION[index].GetPositionX(),
                      KARAZHAN_MAIDEN_OF_VIRTUE_RANGED_POSITION[index].GetPositionY(), bot->GetPositionZ(), false,
                      false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);

    return false;
}

bool KarazhanTheCuratorMarkTargetAction::Execute(Event event)
{
    Unit* target = AI_VALUE2(Unit*, "find target", "astral flare");

    if (!target)
        return false;

    if (Group* group = bot->GetGroup())
    {
        constexpr uint8_t skullIconId = 7;
        ObjectGuid skullGuid = group->GetTargetIcon(skullIconId);

        if (skullGuid != target->GetGUID())
            group->SetTargetIcon(skullIconId, bot->GetGUID(), target->GetGUID());
    }

    return false;
}

bool KarazhanTheCuratorPositionBossAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "the curator");

    if (!boss)
        return false;

    if (!botAI->IsTank(bot))
        return false;

    if (botAI->HasAggro(boss) && boss->GetVictim() == bot)
    {
        const float distanceToBossPosition = boss->GetExactDist2d(KARAZHAN_THE_CURATOR_BOSS_POSITION);

        if (distanceToBossPosition > 5.0f)
        {
            float dirX = KARAZHAN_THE_CURATOR_BOSS_POSITION.GetPositionX() - boss->GetPositionX();
            float dirY = KARAZHAN_THE_CURATOR_BOSS_POSITION.GetPositionY() - boss->GetPositionY();

            float moveX = KARAZHAN_THE_CURATOR_BOSS_POSITION.GetPositionX() + (dirX / distanceToBossPosition) * 4.0f;
            float moveY = KARAZHAN_THE_CURATOR_BOSS_POSITION.GetPositionY() + (dirY / distanceToBossPosition) * 4.0f;

            return MoveTo(bot->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false, false, false,
                          MovementPriority::MOVEMENT_FORCED, true, false);
        }
    }

    return false;
}

bool KarazhanTheCuratorSpreadRangedAction::Execute(Event /*event*/)
{
    if (!botAI->IsRanged(bot))
        return false;

    const float minDistance = 5.0f;
    Unit* nearestPlayer = nullptr;
    float nearestDistance = 1000.0f;

    const GuidVector members = AI_VALUE(GuidVector, "group members");

    for (const auto& memberGuid : members)
    {
        Unit* member = botAI->GetUnit(memberGuid);

        if (!member || !member->IsAlive() || member == bot || bot->GetExactDist2d(member) > minDistance)
            continue;

        float distance = bot->GetExactDist2d(member);

        if (nearestDistance > distance)
        {
            nearestPlayer = member;
            nearestDistance = distance;
        }
    }

    if (!nearestPlayer)
        return false;

    if (bot->GetExactDist2d(nearestPlayer) < minDistance)
        return FleePosition(nearestPlayer->GetPosition(), minDistance);

    return false;
}

bool KarazhanTerestianIllhoofMarkTargetAction::Execute(Event event)
{
    Unit* target = AI_VALUE2(Unit*, "find target", "demon chains");

    if (!target)
        return false;

    if (Group* group = bot->GetGroup())
    {
        constexpr uint8_t skullIconId = 7;
        ObjectGuid skullGuid = group->GetTargetIcon(skullIconId);

        if (skullGuid != target->GetGUID())
            group->SetTargetIcon(skullIconId, bot->GetGUID(), target->GetGUID());
    }

    return false;
}

bool KarazhanShadeOfAranArcaneExplosionAction::Execute(Event /*event*/)
{
    if (!bot->IsAlive())
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "shade of aran");

    if (!boss)
        return false;

    if (!(boss->HasUnitState(UNIT_STATE_CASTING) && boss->FindCurrentSpellBySpellId(SPELL_ARCANE_EXPLOSION)))
        return false;

    const float safeDistance = 20.0f;
    const float distance = bot->GetDistance2d(boss);

    bot->AttackStop();
    bot->InterruptNonMeleeSpells(false);

    if (distance < safeDistance)
        return MoveAway(boss, safeDistance - distance);

    return true;
}

bool KarazhanShadeOfAranFlameWreathAction::Execute(Event /*event*/)
{
    if (!bot->IsAlive())
        return false;

    bool shouldStay = false;
    const float safeDistance = 10.0f;
    const GuidVector members = AI_VALUE(GuidVector, "group members");

    for (const auto& memberGuid : members)
    {
        Unit* member = botAI->GetUnit(memberGuid);

        if (!member || !member->IsAlive() || member == bot)
            continue;

        float distance = bot->GetExactDist2d(member);

        if (distance < safeDistance)
        {
            if (member->HasAura(SPELL_FLAME_WREATH))
            {
                shouldStay = true;
                break;
            }
        }
    }

    if (shouldStay || bot->HasAura(SPELL_FLAME_WREATH))
    {
        AI_VALUE(LastMovement&, "last movement").Set(nullptr);
        bot->GetMotionMaster()->Clear();

        if (bot->isMoving())
            bot->StopMoving();
    }

    return false;
}

bool KarazhanShadeOfAranMarkTargetAction::Execute(Event /*event*/)
{
    Unit* target = nullptr;
    const GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");

    for (const auto& npcGuid : npcs)
    {
        Unit* unit = botAI->GetUnit(npcGuid);

        if (!unit || !unit->IsAlive())
            continue;

        if (unit->GetEntry() == NPC_CONJURED_ELEMENTAL)
        {
            target = unit;
            break;
        }
    }

    if (!target)
        return false;

    if (Group* group = bot->GetGroup())
    {
        constexpr uint8_t skullIconId = 7;
        ObjectGuid skullGuid = group->GetTargetIcon(skullIconId);

        if (Unit* unit = botAI->GetUnit(skullGuid))
            if (unit->GetEntry() == NPC_CONJURED_ELEMENTAL && unit->IsAlive())
                return false;

        if (skullGuid != target->GetGUID())
            group->SetTargetIcon(skullIconId, bot->GetGUID(), target->GetGUID());
    }

    return false;
}

bool KarazhanShadeOfAranSpreadRangedAction::Execute(Event /*event*/)
{
    if (!bot->IsAlive())
        return false;

    if (!botAI->IsRanged(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "shade of aran");

    if (!boss)
        return false;

    if (boss->HasUnitState(UNIT_STATE_CASTING) && boss->FindCurrentSpellBySpellId(SPELL_ARCANE_EXPLOSION))
        return false;

    const GuidVector members = AI_VALUE(GuidVector, "group members");

    for (const auto& memberGuid : members)
    {
        Unit* member = botAI->GetUnit(memberGuid);

        if (!member || !member->IsAlive())
            continue;

        if (member->HasAura(SPELL_FLAME_WREATH))
            return false;
    }

    const float maxBossDistance = 12.0f;
    float bossDistance = bot->GetExactDist2d(boss);

    if (bossDistance > maxBossDistance)
    {
        float dirX = bot->GetPositionX() - boss->GetPositionX();
        float dirY = bot->GetPositionY() - boss->GetPositionY();
        float length = std::sqrt(dirX * dirX + dirY * dirY);

        dirX /= length;
        dirY /= length;

        float targetX = boss->GetPositionX() + dirX * maxBossDistance;
        float targetY = boss->GetPositionY() + dirY * maxBossDistance;

        return MoveTo(bot->GetMapId(), targetX, targetY, bot->GetPositionZ(), false, false, false, true,
                        MovementPriority::MOVEMENT_COMBAT);
    }

    const float minPlayerDistance = 5.0f;
    Unit* nearestPlayer = nullptr;
    float nearestDistance = 1000.0f;

    for (const auto& memberGuid : members)
    {
        Unit* member = botAI->GetUnit(memberGuid);

        if (!member || !member->IsAlive() || member == bot || bot->GetExactDist2d(member) > minPlayerDistance)
            continue;

        float distance = bot->GetExactDist2d(member);

        if (nearestDistance > distance)
        {
            nearestPlayer = member;
            nearestDistance = distance;
        }
    }

    if (!nearestPlayer)
        return false;

    if (bot->GetExactDist2d(nearestPlayer) < minPlayerDistance)
        return FleePosition(nearestPlayer->GetPosition(), minPlayerDistance);

    return false;
}
