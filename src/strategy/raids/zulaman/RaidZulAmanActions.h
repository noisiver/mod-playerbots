#ifndef _PLAYERBOT_RAIDZULAMANACTIONS_H
#define _PLAYERBOT_RAIDZULAMANACTIONS_H

#include "AttackAction.h"

enum ZulAmanNpcs
{
    NPC_AMANI_HEALING_WARD      = 23757,
    NPC_AMANI_PROTECTIVE_WARD   = 23822
};

const Position ZULAMAN_NALORAKK_BOSS_POSITION = Position(-80.12028f, 1330.9705f, 40.77305f);

class ZulAmanTrashMarkTotemsAction : public AttackAction
{
public:
    ZulAmanTrashMarkTotemsAction(PlayerbotAI* botAI, std::string const name = "zulaman trash mark totems")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event event) override;
};

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
