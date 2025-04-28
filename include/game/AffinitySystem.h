#pragma once
#include <string>

class AffinitySystem
{
public:
    static float getAffinityMultiplier(const std::string &attackerAffinity, const std::string &defenderAffinity)
    {
        if ((attackerAffinity == "FIR" && defenderAffinity == "ICE") ||
            (attackerAffinity == "ICE" && defenderAffinity == "ERT") ||
            (attackerAffinity == "ERT" && defenderAffinity == "LGT") ||
            (attackerAffinity == "LGT" && defenderAffinity == "WTR") ||
            (attackerAffinity == "WTR" && defenderAffinity == "FIR"))
            return 1.5f; // Super effective

        if ((attackerAffinity == "ICE" && defenderAffinity == "FIR") ||
            (attackerAffinity == "ERT" && defenderAffinity == "ICE") ||
            (attackerAffinity == "LGT" && defenderAffinity == "ERT") ||
            (attackerAffinity == "WTR" && defenderAffinity == "LGT") ||
            (attackerAffinity == "FIR" && defenderAffinity == "WTR"))
            return 0.5f; // Not very effective

        return 1.0f; // Normal effectiveness
    }
};
