#ifndef _PLAYERBOT_RAIDKARAZHANACTIONS_CONTEXT_H
#define _PLAYERBOT_RAIDKARAZHANACTIONS_CONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "RaidKarazhanActions.h"

class RaidKarazhanActionContext : public NamedObjectContext<Action>
{
public:
    RaidKarazhanActionContext()
    {
        creators["karazhan attumen stay close"] = &RaidKarazhanActionContext::karazhan_attumen_stay_close;
    }

private:
    static Action* karazhan_attumen_stay_close(PlayerbotAI* ai) { return new KarazhanAttumenStayCloseAction(ai); }
};

#endif
