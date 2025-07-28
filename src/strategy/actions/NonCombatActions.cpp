/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NonCombatActions.h"

#include "Event.h"
#include "Playerbots.h"

bool DrinkAction::Execute(Event event)
{
    if (bot->IsInCombat())
        return false;

    bool hasMana = AI_VALUE2(bool, "has mana", "self target");
    if (!hasMana)
        return false;

    if (sPlayerbotAIConfig->freeFood)
    {
        // if (bot->IsNonMeleeSpellCast(true))
        //     return false;

        bot->ClearUnitState(UNIT_STATE_CHASE);
        bot->ClearUnitState(UNIT_STATE_FOLLOW);

        if (bot->isMoving())
        {
            bot->StopMoving();
            // botAI->SetNextCheckDelay(sPlayerbotAIConfig->globalCoolDown);
            // return false;
        }
        bot->SetStandState(UNIT_STAND_STATE_SIT);
        botAI->InterruptSpell();

        // float hp = bot->GetHealthPercent();
        float mp = bot->GetPowerPct(POWER_MANA);
        float p = mp;
        float delay;

        if (!bot->InBattleground())
            delay = 18000.0f * (100 - p) / 100.0f;
        else
            delay = 12000.0f * (100 - p) / 100.0f;

        botAI->SetNextCheckDelay(delay);

        uint8 level = bot->GetLevel();
        uint32 spellId1 = 24707;
        uint32 spellId2 = 24707;
        if (level < 5)
        {
            spellId1 = 433;
            spellId2 = 430;
        }
        else if (level < 15)
        {
            spellId1 = 434;
            spellId2 = 431;
        }
        else if (level < 25)
        {
            spellId1 = 435;
            spellId2 = 432;
        }
        else if (level < 35)
        {
            spellId1 = 1127;
            spellId2 = 1133;
        }
        else if (level < 45)
        {
            spellId1 = 1129;
            spellId2 = 1135;
        }
        else if (level < 55)
        {
            spellId1 = 1131;
            spellId2 = 1137;
        }
        else if (level < 60)
        {
            spellId1 = 1131;
            spellId2 = 22734;
        }
        else if (level < 65)
        {
            spellId1 = 29073;
            spellId2 = 34291;
        }
        else if (level < 70)
        {
            spellId1 = 33725;
            spellId2 = 27089;
        }
        else if (level < 80)
        {
            spellId1 = 33725;
            spellId2 = 46755;
        }
        else
        {
            spellId1 = 45548;
            spellId2 = 57073;
        }

        bot->AddAura(spellId1, bot);
        if (bot->getPowerType() == POWER_MANA)
        {
            bot->AddAura(spellId2, bot);
        }

        return true;
        // return botAI->CastSpell(24707, bot);
    }

    return UseItemAction::Execute(event);
}

bool DrinkAction::isUseful() { return UseItemAction::isUseful() && AI_VALUE2(uint8, "mana", "self target") < 85; }

bool DrinkAction::isPossible()
{
    return !bot->IsInCombat() && (sPlayerbotAIConfig->freeFood || UseItemAction::isPossible());
}

bool EatAction::Execute(Event event)
{
    if (bot->IsInCombat())
        return false;

    if (sPlayerbotAIConfig->freeFood)
    {
        // if (bot->IsNonMeleeSpellCast(true))
        //     return false;

        bot->ClearUnitState(UNIT_STATE_CHASE);
        bot->ClearUnitState(UNIT_STATE_FOLLOW);

        if (bot->isMoving())
        {
            bot->StopMoving();
            // botAI->SetNextCheckDelay(sPlayerbotAIConfig->globalCoolDown);
            // return false;
        }

        bot->SetStandState(UNIT_STAND_STATE_SIT);
        botAI->InterruptSpell();

        float hp = bot->GetHealthPct();
        // float mp = bot->HasMana() ? bot->GetPowerPercent() : 0.f;
        float p = hp;
        float delay;

        if (!bot->InBattleground())
            delay = 18000.0f * (100 - p) / 100.0f;
        else
            delay = 12000.0f * (100 - p) / 100.0f;

        botAI->SetNextCheckDelay(delay);

        uint8 level = bot->GetLevel();
        uint32 spellId1 = 24707;
        uint32 spellId2 = 24707;
        if (level < 5)
        {
            spellId1 = 433;
            spellId2 = 430;
        }
        else if (level < 15)
        {
            spellId1 = 434;
            spellId2 = 431;
        }
        else if (level < 25)
        {
            spellId1 = 435;
            spellId2 = 432;
        }
        else if (level < 35)
        {
            spellId1 = 1127;
            spellId2 = 1133;
        }
        else if (level < 45)
        {
            spellId1 = 1129;
            spellId2 = 1135;
        }
        else if (level < 55)
        {
            spellId1 = 1131;
            spellId2 = 1137;
        }
        else if (level < 60)
        {
            spellId1 = 1131;
            spellId2 = 22734;
        }
        else if (level < 65)
        {
            spellId1 = 29073;
            spellId2 = 34291;
        }
        else if (level < 70)
        {
            spellId1 = 33725;
            spellId2 = 27089;
        }
        else if (level < 80)
        {
            spellId1 = 33725;
            spellId2 = 46755;
        }
        else
        {
            spellId1 = 45548;
            spellId2 = 57073;
        }

        bot->AddAura(spellId1, bot);
        if (bot->getPowerType() == POWER_MANA)
        {
            bot->AddAura(spellId2, bot);
        }

        return true;
    }

    return UseItemAction::Execute(event);
}

bool EatAction::isUseful() { return UseItemAction::isUseful() && AI_VALUE2(uint8, "health", "self target") < 85; }

bool EatAction::isPossible()
{
    return !bot->IsInCombat() && (sPlayerbotAIConfig->freeFood || UseItemAction::isPossible());
}
