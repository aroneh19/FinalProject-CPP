// Character.h
#pragma once

#include <string>
#include <vector>
#include "battle/Skill.h"
#include "game/Stats.h"  


class Character
{

public:
    std::string name;
    std::string affinity;
    std::string description;
    std::string role;

    Stats stats;
    Skill skill;

    const Stats& getStats() const { return stats;}
    const std::string &getName() const { return name; }
    const std::string &getAffinity() const { return affinity; }
    const Skill &getSkill() const { return skill; }
};
