#include "utils/AffinityUtils.h"

bool AffinityUtils::isWeakAgainst(const std::string& targetAffinity, const std::string& attackAffinity) {
    if (attackAffinity == "FIR" && targetAffinity == "ICE") return true;
    if (attackAffinity == "ICE" && targetAffinity == "WTR") return true;
    if (attackAffinity == "LGT" && targetAffinity == "ERT") return true;
    if (attackAffinity == "WTR" && targetAffinity == "FIR") return true;
    if (attackAffinity == "ERT" && targetAffinity == "LGT") return true;

    return false; 
}
