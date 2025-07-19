#ifndef _PLAYERBOT_RAIDZULAMANTRIGGERS_H
#define _PLAYERBOT_RAIDZULAMANTRIGGERS_H

#include "Trigger.h"

class ZulAmanNalorakkTrigger : public Trigger
{
public:
    ZulAmanNalorakkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zulaman nalorakk") {}
    bool IsActive() override;
};

#endif
