#pragma once
#include <string>
#include "game/Stats.h"
#include "battle/Skill.h"

class CharacterBase {
protected:
    std::string name;
    std::string affinity;
    Stats stats;
    Skill skill;

public:
    virtual ~CharacterBase() = default;

    const std::string& getName() const { return name; }
    const std::string& getAffinity() const { return affinity; }
    const Stats& getStats() const { return stats; }
    const Skill& getSkill() const { return skill; }

    void setName(const std::string& n) { name = n; }
    void setAffinity(const std::string& a) { affinity = a; }
    void setStats(const Stats& s) { stats = s; }
    void setSkill(const Skill& sk) { skill = sk; }

    virtual int attack(CharacterBase& target) = 0;
};
