#ifndef _PLAYERBOT_RAIDKARAZHANTRIGGERS_H
#define _PLAYERBOT_RAIDKARAZHANTRIGGERS_H

#include "Trigger.h"

class KarazhanMoroesTrigger : public Trigger
{
public:
    KarazhanMoroesTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan moroes") {}
    bool IsActive() override;
};

class KarazhanMaidenOfVirtueTrigger : public Trigger
{
public:
    KarazhanMaidenOfVirtueTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan maiden of virtue") {}
    bool IsActive() override;
};

class KarazhanRomuloJulianneTrigger : public Trigger
{
public:
    KarazhanRomuloJulianneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan romulo julianne") {}
    bool IsActive() override;
};

class KarazhanWizardOfOzTrigger : public Trigger
{
public:
    KarazhanWizardOfOzTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan wizard of oz") {}
    bool IsActive() override;
};

class KarazhanTheCuratorTrigger : public Trigger
{
public:
    KarazhanTheCuratorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan the curator") {}
    bool IsActive() override;
};

class KarazhanTerestianIllhoofTrigger : public Trigger
{
public:
    KarazhanTerestianIllhoofTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan terestian illhoof") {}
    bool IsActive() override;
};

class KarazhanShadeOfAranTrigger : public Trigger
{
public:
    KarazhanShadeOfAranTrigger(PlayerbotAI* botAI) : Trigger(botAI, "karazhan shade of aran") {}
    bool IsActive() override;
};

#endif
