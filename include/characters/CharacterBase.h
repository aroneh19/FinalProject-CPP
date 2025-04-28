#pragma once
#include <string>
#include "game/Stats.h"

class CharacterBase
{
protected:
    std::string name;
    std::string affinity;
    Stats stats;

public:
    virtual ~CharacterBase() = default;

    const std::string &getName() const { return name; }
    const std::string &getAffinity() const { return affinity; }
    const Stats &getStats() const { return stats; }

    void setName(const std::string &n) { name = n; }
    void setAffinity(const std::string &a) { affinity = a; }
    void setStats(const Stats &s) { stats = s; }

    virtual int attack(CharacterBase &target) = 0;
};
