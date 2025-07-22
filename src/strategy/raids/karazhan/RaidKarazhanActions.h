#ifndef _PLAYERBOT_RAIDKARAZHANACTIONS_H
#define _PLAYERBOT_RAIDKARAZHANACTIONS_H

#include "AttackAction.h"

enum KarazhanSpells
{
    // Maiden of Virtue
    SPELL_REPENTANCE            = 29511,

    // Shade of Aran
    SPELL_FLAME_WREATH          = 29946,
    SPELL_ARCANE_EXPLOSION      = 29973
};

enum KarazhanNpcs
{
    // Shade of Aran
    NPC_CONJURED_ELEMENTAL      = 17167
};

const Position KARAZHAN_MAIDEN_OF_VIRTUE_BOSS_POSITION = Position(-10945.881f, -2103.7817f, 92.71163f);
const Position KARAZHAN_MAIDEN_OF_VIRTUE_RANGED_POSITION[8] =
{
    { -10931.178f, -2116.58f, 92.1787f },
    { -10925.828f, -2102.425f, 92.18016f },
    { -10933.089f, -2088.5017f, 92.18028f },
    { -10947.59f, -2082.8147f, 92.18024f },
    { -10960.912f, -2090.4368f, 92.17964f },
    { -10966.017f, -2105.288f, 92.17582f },
    { -10959.242f, -2119.6172f, 92.18062f },
    { -10944.495f, -2123.857f, 92.18021f },
};

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

class KarazhanMaidenOfVirtuePositionRangedAction : public AttackAction
{
public:
    KarazhanMaidenOfVirtuePositionRangedAction(PlayerbotAI* botAI, std::string const name = "karazhan maiden of virtue position ranged") : AttackAction(botAI, name) {}

    bool Execute(Event /*event*/) override;
};

class KarazhanRomuloJulianneMarkTargetAction : public AttackAction
{
public:
    KarazhanRomuloJulianneMarkTargetAction(PlayerbotAI* botAI, std::string const name = "karazhan romulo julianne mark target") : AttackAction(botAI, name) {}

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
