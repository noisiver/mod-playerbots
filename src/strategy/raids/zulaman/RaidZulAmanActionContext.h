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
        creators["zulaman trash mark totems"] = &RaidZulAmanActionContext::zulaman_trash_mark_totems;
        creators["zulaman nalorakk tank position"] = &RaidZulAmanActionContext::zulaman_nalorakk_tank_position;
        creators["zulaman nalorakk ranged position"] = &RaidZulAmanActionContext::zulaman_nalorakk_ranged_position;

        creators["zulaman akilzon electrical storm"] = &RaidZulAmanActionContext::zulaman_akilzon_electrical_storm;
        creators["zulaman akilzon tank position"] = &RaidZulAmanActionContext::zulaman_akilzon_tank_position;
        creators["zulaman akilzon ranged position"] = &RaidZulAmanActionContext::zulaman_akilzon_ranged_position;
    }

private:
    static Action* zulaman_trash_mark_totems(PlayerbotAI* ai) { return new ZulAmanTrashMarkTotemsAction(ai); }
    static Action* zulaman_nalorakk_tank_position(PlayerbotAI* ai) { return new ZulAmanNalorakkTankPositionAction(ai); }
    static Action* zulaman_nalorakk_ranged_position(PlayerbotAI* ai) { return new ZulAmanNalorakkRangedPositionAction(ai); }

    static Action* zulaman_akilzon_electrical_storm(PlayerbotAI* ai) { return new ZulAmanAkilzonElectricalStormAction(ai); }
    static Action* zulaman_akilzon_tank_position(PlayerbotAI* ai) { return new ZulAmanAkilzonTankPositionAction(ai); }
    static Action* zulaman_akilzon_ranged_position(PlayerbotAI* ai) { return new ZulAmanAkilzonRangedPositionAction(ai); }
};

#endif
