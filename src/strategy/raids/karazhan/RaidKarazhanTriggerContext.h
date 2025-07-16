#ifndef _PLAYERBOT_RAIDKARAZHANTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDKARAZHANTRIGGERCONTEXT_H

#include "RaidKarazhanTriggers.h"

class RaidKarazhanTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidKarazhanTriggerContext()
    {
        creators["karazhan attumen"] = &RaidKarazhanTriggerContext::karazhan_attumen;
    }

private:
    static Trigger* karazhan_attumen(PlayerbotAI* ai) { return new KarazhanAttumenTrigger(ai); }
};

#endif
