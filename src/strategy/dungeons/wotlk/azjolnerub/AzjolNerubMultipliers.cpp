#include "AzjolNerubMultipliers.h"
#include "AzjolNerubActions.h"
#include "GenericSpellActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"
#include "AzjolNerubTriggers.h"
#include "Action.h"

float KrikthirMultiplier::GetValue(Action* action)
{
    // Target is not findable from threat table using AI_VALUE2(),
    // therefore need to search manually for the unit name
    Unit* boss = nullptr;
    Unit* watcher = nullptr;
    GuidVector targets = AI_VALUE(GuidVector, "possible targets no los");

    for (auto i = targets.begin(); i != targets.end(); ++i)
    {
        Unit* unit = botAI->GetUnit(*i);
        if (!unit) { continue; }

        switch (unit->GetEntry())
        {
            case NPC_KRIKTHIR:
                boss = unit;
                continue;
            case NPC_WATCHER_SILTHIK:
            case NPC_WATCHER_GASHRA:
            case NPC_WATCHER_NARJIL:
            case NPC_WATCHER_SKIRMISHER:
            case NPC_WATCHER_SHADOWCASTER:
            case NPC_WATCHER_WARRIOR:
                watcher = unit;
                continue;
        }
    }

    if (boss && watcher)
    {
        // Do not target swap
        // TODO: Need to suppress AoE actions but unsure how to identify them
        // TODO: TEST AOE Avoid
        if (dynamic_cast<DpsAssistAction*>(action)
            || dynamic_cast<DpsAoeAction*>(action))
        {
            return 0.0f;
        }
        // Doesn't seem to work
        // if (action->getThreatType() == Action::ActionThreatType::Aoe)
        // {
        //     bot->Yell("Suppressed AoE", LANG_UNIVERSAL);
        //     return 0.0f;
        // }
    }
    return 1.0f;
}
