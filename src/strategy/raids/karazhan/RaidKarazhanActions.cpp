#include "Playerbots.h"
#include "RaidKarazhanActions.h"

bool KarazhanAttumenStayCloseAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "attumen the huntsman");

    if (!boss)
        return false;

    Unit* soaker = nullptr;
    const GuidVector members = AI_VALUE(GuidVector, "group members");

    for (const auto& memberGuid : members)
    {
        Unit* unit = botAI->GetUnit(memberGuid);

        if (!unit->IsAlive())
            continue;

        if (!botAI->IsRanged(unit->ToPlayer()))
            continue;

        if (unit->ToPlayer()->HasSkill(SKILL_MAIL) || unit->ToPlayer()->HasSkill(SKILL_PLATE_MAIL))
        {
            soaker = unit;
            break;
        }
    }

    const float distance = bot->GetDistance(boss);

    if (soaker && soaker == bot)
    {
        if (distance < 8.0f)
        {
            float angle = bot->GetAngle(boss);
            float x = bot->GetPositionX() + cos(angle) * -8.0f;
            float y = bot->GetPositionY() + sin(angle) * -8.0f;
            return MoveTo(bot->GetMapId(), x, y, bot->GetPositionZ(), false, false, false, false,
                          MovementPriority::MOVEMENT_COMBAT);
        }
    }
    else
    {
        if (distance > 7.0f)
        {
            return MoveTo(boss);
        }
    }

    return false;
}
