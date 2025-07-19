#ifndef _PLAYERBOT_RAIDZULAMANACTIONS_CONTEXT_H
#define _PLAYERBOT_RAIDZULAMANACTIONS_CONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidZulAmanActions.h"

class RaidZulAmanActionContext : public NamedObjectContext<Action>
{
public:
    RaidZulAmanActionContext()
    {
        creators["zulaman nalorakk tank position"] = &RaidZulAmanActionContext::zulaman_nalorakk_tank_position;
    }

private:
    static Action* zulaman_nalorakk_tank_position(PlayerbotAI* ai) { return new ZulAmanNalorakkTankPositionAction(ai); }
};

#endif
