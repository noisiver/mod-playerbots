#ifndef _PLAYERBOT_RAIDZULAMANTRIGGERCONTEXT_H
#define _PLAYERBOT_RAIDZULAMANTRIGGERCONTEXT_H

#include "AiObjectContext.h"
#include "RaidZulAmanTriggers.h"

class RaidZulAmanTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidZulAmanTriggerContext()
    {
        creators["zulaman trash"] = &RaidZulAmanTriggerContext::zulaman_trash;
        creators["zulaman nalorakk"] = &RaidZulAmanTriggerContext::zulaman_nalorakk;
        creators["zulaman akilzon"] = &RaidZulAmanTriggerContext::zulaman_akilzon;
    }

private:
    static Trigger* zulaman_trash(PlayerbotAI* ai) { return new ZulAmanTrashTrigger(ai); }
    static Trigger* zulaman_nalorakk(PlayerbotAI* ai) { return new ZulAmanNalorakkTrigger(ai); }
    static Trigger* zulaman_akilzon(PlayerbotAI* ai) { return new ZulAmanAkilzonTrigger(ai); }
};

#endif
