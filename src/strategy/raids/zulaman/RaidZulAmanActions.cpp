#include "Playerbots.h"
#include "RaidZulAmanActions.h"

bool ZulAmanNalorakkTankPositionAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "nalorakk");

    if (!boss)
        return false;

    if (!botAI->IsTank(bot))
        return false;

    if (botAI->HasAggro(boss) && boss->GetVictim() == bot)
    {
        // Move the boss into position
        const float distanceToBossPosition = boss->GetExactDist2d(ZULAMAN_NALORAKK_BOSS_POSITION);

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
        float targetOrientation = M_PI + M_PI / 2;
        float currentOrientation = boss->GetOrientation();

        currentOrientation = fmod(currentOrientation + 2 * M_PI, 2 * M_PI);
        targetOrientation = fmod(targetOrientation + 2 * M_PI, 2 * M_PI);

        float orientationDiff = currentOrientation - targetOrientation;

        if (std::abs(orientationDiff) > 0.15f)
        {
            float currentX = bot->GetPositionX();
            float currentY = bot->GetPositionY();
            float centerX = boss->GetPositionX();
            float centerY = boss->GetPositionY();
            float radius = std::max(2.0f, bot->GetExactDist2d(centerX, centerY));

            float angle = atan2(currentY - centerY, currentX - centerX);

            float arcStep = 0.125f;
            if (orientationDiff < 0)
                angle += arcStep;
            else
                angle -= arcStep;

            float moveX = centerX + radius * cos(angle);
            float moveY = centerY + radius * sin(angle);

            return MoveTo(bot->GetMapId(), moveX, moveY, bot->GetPositionZ(), false, false, false, false,
                          MovementPriority::MOVEMENT_FORCED, true, false);
        }
    }

    return false;
}
