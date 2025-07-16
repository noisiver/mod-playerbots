#ifndef _PLAYERBOT_RAIDKARAZHANTRIGGERS_H
#define _PLAYERBOT_RAIDKARAZHANTRIGGERS_H

#include "Trigger.h"

class KarazhanAttumenTrigger : public Trigger
{
public:
    KarazhanAttumenTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan attumen") {}
    bool IsActive() override;
};

#endif
