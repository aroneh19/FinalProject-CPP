#pragma once

#include <string>
#include <vector>
#include "battle/Skill.h"
#include "characters/Character.h"

class Enemy
{
public:
    std::string name;
    std::string affinity;
    Stats stats;
    Skill skill;
    int tier;

    const Stats &getStats() const { return stats; }
    const std::string &getName() const { return name; }
    const std::string &getAffinity() const { return affinity; }
    const Skill &getSkill() const { return skill; }
    int getTier() const { return tier; }
};
