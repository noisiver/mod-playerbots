#include "RaidKarazhanActions.h"
#include "RaidKarazhanHelpers.h"

void RaidKarazhanHelpers::MarkTargetWithSkull(Unit* target)
{
    if (!target)
        return;

    if (Group* group = bot->GetGroup())
    {
        constexpr uint8_t skullIconId = 7;
        ObjectGuid skullGuid = group->GetTargetIcon(skullIconId);

        if (skullGuid != target->GetGUID())
            group->SetTargetIcon(skullIconId, bot->GetGUID(), target->GetGUID());
    }
}

Unit* RaidKarazhanHelpers::GetFirstAliveUnit(const std::vector<Unit*>& units)
{
    for (Unit* unit : units)
        if (unit && unit->IsAlive())
            return unit;

    return nullptr;
}

Unit* RaidKarazhanHelpers::GetFirstAliveUnitByEntry(uint32 entry)
{
    const GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");

    for (const auto& npcGuid : npcs)
    {
        Unit* unit = botAI->GetUnit(npcGuid);

        if (unit && unit->IsAlive() && unit->GetEntry() == entry)
            return unit;
    }

    return nullptr;
}

Unit* RaidKarazhanHelpers::GetNearestPlayer(float radius)
{
    if (Group* group = bot->GetGroup())
    {
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* member = itr->GetSource();

            if (!member || !member->IsAlive() || member == bot)
                continue;

            if (bot->GetExactDist2d(member) < radius)
                return member;
        }
    }

    return nullptr;
}

bool RaidKarazhanHelpers::IsFlameWreathActive()
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

            if (member->HasAura(SPELL_FLAME_WREATH))
                return true;
        }
    }

    return false;
}

bool RaidKarazhanHelpers::IsBetween(Unit* first, Unit* second)
{
    float bx = first->GetPositionX();
    float by = first->GetPositionY();
    float px = second->GetPositionX();
    float py = second->GetPositionY();
    float botx = bot->GetPositionX();
    float boty = bot->GetPositionY();

    // Vector from boss to portal
    float dx = px - bx;
    float dy = py - by;

    // Vector from boss to bot
    float botdx = botx - bx;
    float botdy = boty - by;

    // Project bot position onto the line segment [boss, portal]
    float lenSq = dx * dx + dy * dy;
    float t = (lenSq > 0) ? ((botdx * dx + botdy * dy) / lenSq) : 0.0f;
    t = std::clamp(t, 0.0f, 1.0f);

    // Closest point on the line segment
    float closestX = bx + t * dx;
    float closestY = by + t * dy;

    // Distance from bot to the closest point on the line
    float dist = std::sqrt((botx - closestX) * (botx - closestX) + (boty - closestY) * (boty - closestY));

    return dist < 1.0f;
}
