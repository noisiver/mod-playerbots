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
    }

private:
    static Trigger* zulaman_trash(PlayerbotAI* ai) { return new ZulAmanTrashTrigger(ai); }
    static Trigger* zulaman_nalorakk(PlayerbotAI* ai) { return new ZulAmanNalorakkTrigger(ai); }
};

#endif
