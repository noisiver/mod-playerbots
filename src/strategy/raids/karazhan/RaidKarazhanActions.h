#ifndef _PLAYERBOT_RAIDKARAZHANACTIONS_H
#define _PLAYERBOT_RAIDKARAZHANACTIONS_H

#include "AttackAction.h"

enum KarazhanSpells
{
    SPELL_FLAME_WREATH      = 29946,
    SPELL_ARCANE_EXPLOSION  = 29973
};

enum KarazhanNpcs
{
    NPC_CONJURED_ELEMENTAL  = 17167
};

const Position KARAZHAN_MAIDEN_OF_VIRTUE_BOSS_POSITION = Position(-10959.8955f, -2120.362f, 92.18005f);
const Position KARAZHAN_THE_CURATOR_BOSS_POSITION = Position(-11139.463f, -1884.6451f, 165.76564f);

class KarazhanMoroesMarkTargetAction : public AttackAction
{
public:
    KarazhanMoroesMarkTargetAction(PlayerbotAI* botAI, std::string const name = "karazhan moroes mark target") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanMaidenOfVirtuePositionBossAction : public AttackAction
{
public:
    KarazhanMaidenOfVirtuePositionBossAction(PlayerbotAI* botAI, std::string const name = "karazhan maiden of virtue position boss") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanMaidenOfVirtueSpreadRangedAction : public AttackAction
{
public:
    KarazhanMaidenOfVirtueSpreadRangedAction(PlayerbotAI* botAI, std::string const name = "karazhan maiden of virtue spread ranged") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanTheCuratorMarkTargetAction : public AttackAction
{
public:
    KarazhanTheCuratorMarkTargetAction(PlayerbotAI* botAI, std::string const name = "karazhan the curator mark target") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanTheCuratorPositionBossAction : public AttackAction
{
public:
    KarazhanTheCuratorPositionBossAction(PlayerbotAI* botAI, std::string const name = "karazhan the curator position boss") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanTheCuratorSpreadRangedAction : public AttackAction
{
public:
    KarazhanTheCuratorSpreadRangedAction(PlayerbotAI* botAI, std::string const name = "karazhan the curator spread ranged") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanTerestianIllhoofMarkTargetAction : public AttackAction
{
public:
    KarazhanTerestianIllhoofMarkTargetAction(PlayerbotAI* botAI, std::string const name = "karazhan terestian illhoof mark target") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanShadeOfAranArcaneExplosionAction : public AttackAction
{
public:
    KarazhanShadeOfAranArcaneExplosionAction(PlayerbotAI* botAI, std::string const name = "karazhan shade of aran arcane explosion") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanShadeOfAranFlameWreathAction : public AttackAction
{
public:
    KarazhanShadeOfAranFlameWreathAction(PlayerbotAI* botAI, std::string const name = "karazhan shade of aran flame wreath") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanShadeOfAranMarkTargetAction : public AttackAction
{
public:
    KarazhanShadeOfAranMarkTargetAction(PlayerbotAI* botAI, std::string const name = "karazhan shade of aran mark target") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanShadeOfAranSpreadRangedAction : public AttackAction
{
public:
    KarazhanShadeOfAranSpreadRangedAction(PlayerbotAI* botAI, std::string const name = "karazhan shade of aran spread ranged") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

#endif
