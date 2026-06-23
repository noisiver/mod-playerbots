#ifndef _PLAYERBOT_RSSCRIPTS_H
#define _PLAYERBOT_RSSCRIPTS_H

#include <map>
#include <unordered_map>
#include <vector>
#include "ObjectGuid.h"
#include "Position.h"

namespace RubySanctumHelpers
{

    struct MeteorPingPong
    {
        uint32 count;
        uint32 lastCastTime;
        uint32 tankMeteorTime;
        uint32 tankReturnTime;
    };

    extern std::unordered_map<uint32, MeteorPingPong> meteorPingPong;

    struct CutterTiming
    {
        uint32 lastShootTime;
        bool active;
        uint32 encounterStart;
        ObjectGuid bossGuid;
        float spinSign;
        float lastOrbAngle;
        bool hasOrbAngle;
    };

    extern std::unordered_map<uint32, CutterTiming> cutterTiming;

    struct PortalAddGate
    {
        uint32 armTime;
        uint32 lastAddAliveTime;
    };

    extern std::unordered_map<uint32, PortalAddGate> portalAddGate;

    extern std::map<std::pair<uint32, ObjectGuid>, bool> p3TwilightAssignment;

    struct HalionCorporeality
    {
        uint8 physicalIndex;
        uint32 physicalStamp;
        uint8 twilightIndex;
        uint32 twilightStamp;
    };

    extern std::unordered_map<uint32, HalionCorporeality> halionCorporeality;

    inline constexpr uint32 HALION_CORPOREALITY_AURAS[11] =
    {
        74836, 74835, 74834, 74833, 74832, 74826, 74827, 74828, 74829, 74830, 74831
    };
}

void AddSC_RubySanctumBotScripts();

#endif
