#ifndef _PLAYERBOT_RAIDZULAMANACTIONS_H
#define _PLAYERBOT_RAIDZULAMANACTIONS_H

#include "AttackAction.h"

const Position ZULAMAN_NALORAKK_BOSS_POSITION = Position(-80.12028f, 1330.9705f, 40.77305f);

class ZulAmanNalorakkTankPositionAction : public AttackAction
{
public:
    ZulAmanNalorakkTankPositionAction(PlayerbotAI* botAI, std::string const name = "zulaman nalorakk tank position")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event event) override;
};

#endif
