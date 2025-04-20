#pragma once

#include "characters/CharacterBase.h"
#include "game/Stats.h"


class Enemy : public CharacterBase {
private:
    int tier;

public:
    Enemy() = default;

    int getTier() const { return tier; }
    void setTier(int t) { tier = t; }

    void setStats(const Stats& s) { stats = s; }
    void setSkill(const Skill& sk) { skill = sk; }
    void setName(const std::string& n) { name = n; }
    void setAffinity(const std::string& a) { affinity = a; }
};
