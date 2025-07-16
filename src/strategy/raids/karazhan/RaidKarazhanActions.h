#ifndef _PLAYERBOT_RAIDKARAZHANACTIONS_H
#define _PLAYERBOT_RAIDKARAZHANACTIONS_H

#include "AttackAction.h"

class KarazhanAttumenStayCloseAction : public AttackAction
{
public:
    KarazhanAttumenStayCloseAction(PlayerbotAI* botAI, std::string const name = "karazhan attumen stay close")
        : AttackAction(botAI, name)
    {
    }

    bool Execute(Event event) override;
};

#endif
