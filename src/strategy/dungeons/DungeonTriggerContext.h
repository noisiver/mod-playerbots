/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_DUNGEONSTRIGGERCONTEXT_H
#define _PLAYERBOT_DUNGEONSTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "AiObjectContext.h"

class DungeonTriggerContext : public NamedObjectContext<Trigger> 
{
    public:
        DungeonTriggerContext() 
        {
        }
    private:
};

#endif
