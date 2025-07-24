#include "Playerbots.h"
#include "RaidKarazhanActions.h"

Unit* GetFirstAliveUnit(std::initializer_list<Unit*> units)
{
    for (Unit* unit : units)
        if (unit && unit->IsAlive())
            return unit;

    return nullptr;
}

Unit* GetAliveUnitByEntry(PlayerbotAI* botAI, const GuidVector& npcs, uint32 entry)
{
    for (const auto& npcGuid : npcs)
    {
        Unit* unit = botAI->GetUnit(npcGuid);

        if (unit && unit->IsAlive() && unit->GetEntry() == entry)
            return unit;
    }

    return nullptr;
}

void SetSkullIcon(Player* bot, Unit* target)
{
    if (Group* group = bot->GetGroup())
    {
        constexpr uint8_t skullIconId = 7;
        ObjectGuid skullGuid = group->GetTargetIcon(skullIconId);

        if (skullGuid != target->GetGUID())
            group->SetTargetIcon(skullIconId, bot->GetGUID(), target->GetGUID());
    }
}

bool HasFlameWreathNearby(Player* bot)
{
    if (bot->HasAura(SPELL_FLAME_WREATH))
        return true;

    if (Group* group = bot->GetGroup())
    {
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* member = itr->GetSource();

            if (!member || !member->IsAlive() || member == bot)
                continue;

            if (member->HasAura(SPELL_FLAME_WREATH) && bot->GetExactDist2d(member) <= 5.0f)
                return true;
        }
    }

    return false;
}

Unit* GetNearestPlayer(Player* bot, float distance)
{
    if (Group* group = bot->GetGroup())
    {
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* member = itr->GetSource();

            if (!member || !member->IsAlive() || member == bot)
                continue;

            if (bot->GetExactDist2d(member) < distance)
                return member;
        }
    }

    return nullptr;
}

Position GetPositionToMoveBoss(Unit* boss, Position position, float radius)
{
    const float distanceToPosition = boss->GetExactDist2d(position);

    float dX = position.GetPositionX() - boss->GetPositionX();
    float dY = position.GetPositionY() - boss->GetPositionY();

    float mX = position.GetPositionX() + (dX / distanceToPosition) * radius;
    float mY = position.GetPositionY() + (dY / distanceToPosition) * radius;
    float mZ = position.GetPositionZ();

    return {mX, mY, mZ};
}

Position GetPositionNearTarget(Unit* target, float radius)
{
    float angle = target->GetOrientation();
    float targetX = target->GetPositionX() + cos(angle) * radius;
    float targetY = target->GetPositionY() + sin(angle) * radius;
    float targetZ = target->GetPositionZ();

    return {targetX, targetY, targetZ};
}

Position GetPositionToMoveCloserToTarget(Player* bot, Unit* target, float radius)
{
    float dX = bot->GetPositionX() - target->GetPositionX();
    float dY = bot->GetPositionY() - target->GetPositionY();
    float length = std::sqrt(dX * dX + dY * dY);

    dX /= length;
    dY /= length;

    float tX = target->GetPositionX() + dX * radius;
    float tY = target->GetPositionY() + dY * radius;

    return {tX, tY, bot->GetPositionZ()};
}

bool KarazhanMoroesMarkTargetAction::Execute(Event event)
{
    Unit* dorothea = AI_VALUE2(Unit*, "find target", "baroness dorothea millstipe");
    Unit* catriona = AI_VALUE2(Unit*, "find target", "lady catriona von'indi");
    Unit* keira = AI_VALUE2(Unit*, "find target", "lady keira berrybuck");
    Unit* rafe = AI_VALUE2(Unit*, "find target", "baron rafe dreuger");
    Unit* robin = AI_VALUE2(Unit*, "find target", "lord robin daris");
    Unit* crispin = AI_VALUE2(Unit*, "find target", "lord crispin ference");
    Unit* target = GetFirstAliveUnit({dorothea, catriona, keira, rafe, robin, crispin});

    if (!target)
        return false;

    SetSkullIcon(bot, target);
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
            {
                healer = nullptr;
                break;
            }

            if (!healer)
                healer = member;
        }
    }

    if (botAI->HasAggro(boss) && boss->GetVictim() == bot)
    {
        float radius = 3.0f;
        float distance = boss->GetExactDist2d(KARAZHAN_MAIDEN_OF_VIRTUE_BOSS_POSITION);
        Position position = GetPositionToMoveBoss(boss, KARAZHAN_MAIDEN_OF_VIRTUE_BOSS_POSITION, radius);

        if (healer)
        {
            radius = 1.0f;
            distance = bot->GetExactDist2d(healer);
            position = GetPositionNearTarget(healer, 6.0f);
        }

        if (distance > radius)
            return MoveTo(bot->GetMapId(), position.GetPositionX(), position.GetPositionY(), bot->GetPositionZ(), false,
                          false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
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

bool KarazhanRomuloJulianneMarkTargetAction::Execute(Event event)
{
    Unit* target = nullptr;
    Unit* romulo = AI_VALUE2(Unit*, "find target", "romulo");
    Unit* julianne = AI_VALUE2(Unit*, "find target", "julianne");

    if (!romulo || !julianne)
        return false;

    const int maxPctDifference = 10;

    if (julianne->GetHealthPct() + maxPctDifference < romulo->GetHealthPct() || julianne->GetHealthPct() < 1.0f)
        target = romulo;
    else if (romulo->GetHealthPct() + maxPctDifference < julianne->GetHealthPct() || romulo->GetHealthPct() < 1.0f)
        target = julianne;

    if (!target)
        return false;

    SetSkullIcon(bot, target);
    return false;
}

bool KarazhanWizardOfOzMarkTargetAction::Execute(Event event)
{
    Unit* dorothee = AI_VALUE2(Unit*, "find target", "dorothee");
    Unit* strawman = AI_VALUE2(Unit*, "find target", "strawman");
    Unit* tinhead = AI_VALUE2(Unit*, "find target", "tinhead");
    Unit* tito = AI_VALUE2(Unit*, "find target", "tito");
    Unit* roar = AI_VALUE2(Unit*, "find target", "roar");
    Unit* crone = AI_VALUE2(Unit*, "find target", "the crone");
    Unit* target = GetFirstAliveUnit({dorothee, strawman, tinhead, tito, roar, crone});

    if (!target)
        return false;

    SetSkullIcon(bot, target);
    return false;
}

bool KarazhanTheCuratorMarkTargetAction::Execute(Event event)
{
    Unit* target = AI_VALUE2(Unit*, "find target", "astral flare");

    if (!target)
        return false;

    SetSkullIcon(bot, target);
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
        const float radius = 3.0f;
        const float distance = boss->GetExactDist2d(KARAZHAN_THE_CURATOR_BOSS_POSITION);

        if (distance > radius)
        {
            const Position targetPosition = GetPositionToMoveBoss(boss, KARAZHAN_THE_CURATOR_BOSS_POSITION, radius);

            return MoveTo(bot->GetMapId(), targetPosition.GetPositionX(), targetPosition.GetPositionY(),
                          bot->GetPositionZ(), false, false, false, false, MovementPriority::MOVEMENT_FORCED, true,
                          false);
        }
    }

    return false;
}

bool KarazhanTheCuratorSpreadRangedAction::Execute(Event /*event*/)
{
    if (!botAI->IsRanged(bot))
        return false;

    const float minDistance = 5.0f;
    Unit* nearestPlayer = GetNearestPlayer(bot, minDistance);

    if (nearestPlayer)
        return FleePosition(nearestPlayer->GetPosition(), minDistance);

    return false;
}

bool KarazhanTerestianIllhoofMarkTargetAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "terestian illhoof");

    if (!boss)
        return false;

    const GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    Unit* target = GetAliveUnitByEntry(botAI, npcs, NPC_DEMON_CHAINS);

    if (!target)
        target = boss;

    SetSkullIcon(bot, target);
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

    if (HasFlameWreathNearby(bot))
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
    
    const GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    Unit* target = GetAliveUnitByEntry(botAI, npcs, NPC_CONJURED_ELEMENTAL);

    if (!target)
        return false;

    SetSkullIcon(bot, target);
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

    if (HasFlameWreathNearby(bot))
        return false;

    const float maxBossDistance = 12.0f;
    float bossDistance = bot->GetExactDist2d(boss);

    if (bossDistance > maxBossDistance)
    {
        const Position position = GetPositionToMoveCloserToTarget(bot, boss, maxBossDistance);

        return MoveTo(bot->GetMapId(), position.GetPositionX(), position.GetPositionY(), bot->GetPositionZ(), false,
                      false, false, true, MovementPriority::MOVEMENT_COMBAT);
    }

    const float minDistance = 5.0f;
    Unit* nearestPlayer = GetNearestPlayer(bot, minDistance);

    if (nearestPlayer)
        return FleePosition(nearestPlayer->GetPosition(), minDistance);

    return false;
}
