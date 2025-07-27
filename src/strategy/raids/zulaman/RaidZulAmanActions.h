#ifndef _PLAYERBOT_RAIDZULAMANACTIONS_H
#define _PLAYERBOT_RAIDZULAMANACTIONS_H

#include "AttackAction.h"

enum ZulAmanNpcs
{
    NPC_AMANI_HEALING_WARD      = 23757,
    NPC_AMANI_PROTECTIVE_WARD   = 23822
};

enum ZulAmanSpells
{
    SPELL_ELECTRICAL_STORM      = 43648
};

const Position ZULAMAN_NALORAKK_BOSS_POSITION = Position(-80.12028f, 1330.9705f, 40.77305f);
const Position ZULAMAN_AKILZON_BOSS_POSITION = Position(376.353f, 1407.34f, 74.793335f);

class ZulAmanTrashMarkTotemsAction : public AttackAction
{
public:
    ZulAmanTrashMarkTotemsAction(PlayerbotAI* botAI, std::string const name = "zulaman trash mark totems")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event /*event*/) override;
};

class ZulAmanNalorakkTankPositionAction : public AttackAction
{
public:
    ZulAmanNalorakkTankPositionAction(PlayerbotAI* botAI, std::string const name = "zulaman nalorakk tank position")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event /*event*/) override;
};

class ZulAmanNalorakkRangedPositionAction : public AttackAction
{
public:
    ZulAmanNalorakkRangedPositionAction(PlayerbotAI* botAI, std::string const name = "zulaman nalorakk ranged position")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event /*event*/) override;
};

class ZulAmanAkilzonElectricalStormAction : public AttackAction
{
public:
    ZulAmanAkilzonElectricalStormAction(PlayerbotAI* botAI, std::string const name = "zulaman akilzon electrical storm")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event /*event*/) override;

private:
    uint32 startTime = 0;
    bool stormActive = false;
};

class ZulAmanAkilzonTankPositionAction : public AttackAction
{
public:
    ZulAmanAkilzonTankPositionAction(PlayerbotAI* botAI, std::string const name = "zulaman akilzon tank position")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event /*event*/) override;
};

class ZulAmanAkilzonRangedPositionAction : public AttackAction
{
public:
    ZulAmanAkilzonRangedPositionAction(PlayerbotAI* botAI, std::string const name = "zulaman akilzon ranged position")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event /*event*/) override;
};

#endif
