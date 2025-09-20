/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */
 
#pragma once

#include <string>
#include <functional>
#include "Common.h"
#include "Group.h"
#include "Chat.h"
#include "Language.h"

class Player;
class PlayerbotAI;

namespace ai::buff
{

    // Build an aura qualifier "single + greater" to avoid double-buffing
    std::string MakeAuraQualifierForBuff(std::string const& name);

    // Returns the group spell name for a given single-target buff.
    // If no group equivalent exists, returns "".
    std::string GroupVariantFor(std::string const& name);

    // Checks if the bot has the required reagents to cast a spell (by its spellId).
    // Returns false if the spellId is invalid.
    bool HasRequiredReagents(Player* bot, uint32 spellId);


    // Applies the "switch to group buff" policy if: the bot is in a group of size x+,
    // the group variant is known/useful, and reagents are available. Otherwise, returns baseName.
    std::string UpgradeToGroupIfAppropriate(
        Player* bot,
        PlayerbotAI* botAI,
        std::string const& baseName
    );
}
