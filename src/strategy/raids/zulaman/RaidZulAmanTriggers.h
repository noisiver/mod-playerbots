#ifndef _PLAYERBOT_RAIDZULAMANTRIGGERS_H
#define _PLAYERBOT_RAIDZULAMANTRIGGERS_H

#include "Trigger.h"

class ZulAmanTrashTrigger : public Trigger
{
public:
    ZulAmanTrashTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zulaman trash") {}
    bool IsActive() override;
};

class ZulAmanNalorakkTrigger : public Trigger
{
public:
    ZulAmanNalorakkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zulaman nalorakk") {}
    bool IsActive() override;
};

class ZulAmanAkilzonTrigger : public Trigger
{
public:
    ZulAmanAkilzonTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zulaman akil'zon") {}
    bool IsActive() override;
};

#endif
